import javax.swing.*;
import java.awt.*;

public class RunMain{

    public static void main(String[] args){
        AppFrame runMain = new AppFrame();
        runMain.setResizable(false);
        runMain.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        runMain.setVisible(true);
        runMain.pack();
    }
}

class AppFrame extends JFrame{
    private static final long serialVersionUID = 1L;

    private String inputDataStr;            // 输入待发送的数据
    private String inputGxStr;              // 输入多项式
    private String outputRedundance;        // 显示的冗余码

    private String inputCRC;                // 输入待校验的CRC
    private boolean checkFlag;              //判断是否出错

    public AppFrame(){
        /**
         * 顶部画板
         */
        JPanel topJPanel = new JPanel();
        ImageIcon icon = new ImageIcon("../img/crc.png");
        JLabel iconLabel = new JLabel(icon);
        topJPanel.add(iconLabel);
        add(topJPanel, BorderLayout.NORTH);

        /**
         * 左侧画板
         */
        JPanel leftJPanel = new JPanel();
        leftJPanel.setLayout(new BoxLayout(leftJPanel, BoxLayout.Y_AXIS));
        leftJPanel.setBorder(BorderFactory.createTitledBorder("发送端"));

        JLabel label1 = new JLabel("请输入二进制数据:");
        JTextField inputData1 = new JTextField(20);
        JLabel label2 = new JLabel("请输入多项式的二进制数据:");
        JTextField inputGx1 = new JTextField(20);
        JLabel label3 = new JLabel("产生的冗余码:");
        JTextField outputRedundance1 = new JTextField(20);
        outputRedundance1.setEditable(false);
        JLabel label4 = new JLabel("CRC校验码:");
        JTextField outputCRC= new JTextField(20);
        outputCRC.setEditable(false);
        
        leftJPanel.add(label1);
        leftJPanel.add(inputData1);
        leftJPanel.add(Box.createVerticalStrut(40));
        leftJPanel.add(label2);
        leftJPanel.add(inputGx1);
        leftJPanel.add(Box.createVerticalStrut(40));
        leftJPanel.add(label3);
        leftJPanel.add(outputRedundance1);
        leftJPanel.add(Box.createVerticalStrut(40));
        leftJPanel.add(label4);
        leftJPanel.add(outputCRC);
       
        add(leftJPanel, BorderLayout.WEST);

        /**
         * 右侧画板
         */
        JPanel rigthPanel = new JPanel();
        rigthPanel.setLayout(new BoxLayout(rigthPanel, BoxLayout.Y_AXIS));
        rigthPanel.setBorder(BorderFactory.createTitledBorder("接收端"));

        JLabel label5 = new JLabel("CRC编码(二进制): ");
        JTextField inputData2 = new JTextField(25);
        JLabel label6 = new JLabel("多项式编码: ");
        JTextField inputGx2 = new JTextField(25);
        JLabel label7 = new JLabel("是否检测到错误: ");
        JTextField outputError = new JTextField(25);
        outputError.setEditable(false);
        JLabel label8 = new JLabel("出错位置：");
        JTextField outputRight = new JTextField(25);
        outputRight.setEditable(false);

        rigthPanel.add(label5);
        rigthPanel.add(inputData2);
        rigthPanel.add(Box.createVerticalStrut(40));
        rigthPanel.add(label6);
        rigthPanel.add(inputGx2);
        rigthPanel.add(Box.createVerticalStrut(40));
        rigthPanel.add(label7);
        rigthPanel.add(outputError);
        rigthPanel.add(Box.createVerticalStrut(40));
        rigthPanel.add(label8);
        rigthPanel.add(outputRight);

        add(rigthPanel, BorderLayout.EAST);
        
        /**
         * 底部按钮画板
         */
        JPanel bottomPanel = new JPanel();
        bottomPanel.setLayout(new BoxLayout(bottomPanel, BoxLayout.X_AXIS));

        JButton sendButton = new JButton("发送");
        sendButton.setPreferredSize(new Dimension(150, 30));
        JLabel mynameLabel = new JLabel("计科1703-张俊峰-2017040330");
        JButton receiveButton = new JButton("接受");
        receiveButton.setPreferredSize(new Dimension(150, 30));

        bottomPanel.add(Box.createVerticalStrut(5));
        bottomPanel.add(sendButton);
        bottomPanel.add(Box.createVerticalStrut(10));
        bottomPanel.add(mynameLabel);
        bottomPanel.add(Box.createVerticalStrut(10));
        bottomPanel.add(receiveButton);
        bottomPanel.add(Box.createVerticalStrut(5));

        add(bottomPanel, BorderLayout.SOUTH);

        sendButton.addActionListener(e->{
            inputDataStr = inputData1.getText();
            inputGxStr = inputGx1.getText();
            inputGx2.setText(inputGxStr);

            try {
                CalcCRC calcCRC = new CalcCRC();
                outputRedundance = calcCRC.calcRedundancy(inputDataStr, inputGxStr);
                outputRedundance1.setText(outputRedundance);
                String binaryString = inputDataStr + outputRedundance;
                String hexString = calcCRC.toHexString(binaryString);
                outputCRC.setText(hexString);
            } catch (Exception x) {
                return;
            }
            
        });

        receiveButton.addActionListener(e->{
            inputCRC = inputData2.getText();
            inputGxStr = inputGx1.getText();
        
            try{
                CalcCRC calcCRCs = new CalcCRC();
                checkFlag = calcCRCs.checkoutError(inputCRC, inputGxStr);
                if (checkFlag)
                    outputError.setText("没出错！");
                else
                    outputError.setText("出错！");
            }catch (Exception x){
                return;
            }
        });
    }

    public Dimension getPreferredSize(){
        return new Dimension(600, 500);
    }

}