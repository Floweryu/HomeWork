# -*- coding:utf-8 -*-
# _author_='Zhang JunFeng'
import time
import threading
import random

gMoney = 0
gLock = threading.Lock()

def produter():
    global gMoney
    while True:
        money = random.randint(0, 100)
        gLock.acquire()
        gMoney += money
        print("%s生产者生产了%s元钱， 剩余%s元钱" % (threading.current_thread(), money, gMoney))
        gLock.release()
        time.sleep(0.5)


def consumer():
    global gMoney
    while True:
        money = random.randint(0, 100)
        gLock.acquire()
        if gMoney >= money:
            gMoney -= money
            print("%s消费者消费了%s元钱， 剩余%s元钱" % (threading.current_thread(), money, gMoney))
        else:
            print("%s消费者想消费%s元钱，但是余额不足！剩余%s元钱" % (threading.current_thread(), money, gMoney))
        gLock.release()
        time.sleep(0.5)


if __name__ == '__main__':
    # line_run()
    # thread_run()
    for x in range(5):
        th = threading.Thread(target=produter)
        th.start()

    for x in range(5):
        th = threading.Thread(target=consumer)
        th.start()

