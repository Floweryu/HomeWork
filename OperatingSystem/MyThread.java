public class MyThread{
    private static Integer count = 0; // 设置 count 初始值
    private static final Integer FULL = 10; // 设置临界区可以存储的最大容量
    private static String LOCK = "lock";    // 设置锁

    public static void main(String[] args) {
         MyThread test = new MyThread();  // 创建一个 test 进程
         //五个生产者进程，五个消费者
         new Thread(test.new Producer()).start();     // 生产者进程
         new Thread(test.new Consumer()).start();     // 消费者进程
         new Thread(test.new Producer()).start();
         new Thread(test.new Consumer()).start();
         new Thread(test.new Producer()).start();
         new Thread(test.new Consumer()).start();
         new Thread(test.new Producer()).start();
         new Thread(test.new Producer()).start();
         new Thread(test.new Consumer()).start();
         new Thread(test.new Consumer()).start();
    }

    // 生产者进程
    class Producer implements Runnable{
        @Override
        public void run()
        {
            for (int i = 0; i < 10; i++)
            {
                try{
                    Thread.sleep(1000);
                } catch(Exception e){
                    e.printStackTrace();
                }
                synchronized (LOCK){
                    while(count == FULL)    //临界区满了，停止生产者进程
                    {
                        try {
                            System.out.println("临界区已满，生产者停止！！");
                            LOCK.wait();   
                        } catch (Exception e) { //异常处理
                            e.printStackTrace();
                        }
                    }
                    count++;
                    System.out.println(Thread.currentThread().getName() + "生产者生产， 目前总共有" + count);
                    LOCK.notifyAll(); //启动所有线程
                }
            }
        }
    }

    //消费者进程
    class Consumer implements Runnable {
        @Override
        public void run() 
        {
            for (int i = 0; i < 10; i++) 
            {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                synchronized (LOCK) {
                    while (count == 0) {  //等到临界区为空时，要等待，进行消费者进程
                        try {
                            System.out.println("临界区已空，消费者停止！！！");
                            LOCK.wait();
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }
                    count--;
                    System.out.println(Thread.currentThread().getName() + "消费者消费，目前总共有" + count);
                    LOCK.notifyAll(); //启动所有线程
                }
            }
        }
    }

}