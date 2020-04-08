import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class App {
    public static void main(String[] args) {
        AppFrame appFrame = new AppFrame();
        appFrame.setResizable(false);
        appFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        appFrame.setVisible(true);
        appFrame.pack();
    }
}


/**
 * AppFrame
 */
class AppFrame extends JFrame{
    private static final long serialVersionUID = 1L;

    private JPanel topPanel = new JPanel();
    private JPanel middlePanel = new JPanel();
    private JPanel bottomPanel = new JPanel();
    private ImageIcon icon;

    private String hammingCode;         // 正确海明码
    private String erroroutString;      // 错误海明码
    
    private JTextField inputCode;       // 输入
    private JTextField leftHamming;    // 显示海明码
    private JButton randomError;        // 随机产生错误码按钮
    private JTextField errorCode;       // 产生错误后的海明码
    private JTextField outError;        // 输出错误位数
    private JTextField middleHamming;    // 正确的海明码
    private JTextField outputCode;      // 接收端数据  
    private JTextField rightErrorHamming;    // 接收端海明码
    private JButton sendButton;         // 发送按钮
    private JButton checkButton;        // 检错按钮

    private CreateHamming encodeHamming;   

    public AppFrame(){
        createFrame();
        actionPerformed();
    }

    public void actionPerformed(){

        sendButton.addActionListener(e->{
            String code = inputCode.getText();
            String regex = "(0|1)*";
            if (code.length() > 10){
                leftHamming.setText("请输入10位以下二进制数据");
                return;
            }
            if (!code.matches(regex)) {
                leftHamming.setText("请输入二进制数据！！！");
                return;
            }
            encodeHamming = new CreateHamming();
            hammingCode = encodeHamming.encodeHamming(code);
            leftHamming.setText(hammingCode);
            middleHamming.setText(hammingCode);
        });

        randomError.addActionListener(e->{
            Random rand = new Random();
            int index = rand.nextInt(hammingCode.length());     // 在海明码长度下随机产生一个位置，用来产生差错
            StringBuffer errorHamming = new StringBuffer(hammingCode);
            if (hammingCode.charAt(index) == '0')
                errorHamming.replace(index, index + 1, "1"); 
            else
                errorHamming.replace(index, index + 1, "0");
            erroroutString = errorHamming.toString();
            errorCode.setText(erroroutString);
            String outError1 = "第" + String.valueOf(index + 1) + "位产生错误";
            outError.setText(outError1);
        });

        checkButton.addActionListener(e->{
            final String checkStr = (erroroutString == null) ? hammingCode : erroroutString;
            rightErrorHamming.setText(checkStr);
            String out1 = encodeHamming.getErrorIndex(checkStr);
            outputCode.setText(out1);
        });
    }

    /**
     * 创建界面
     */
    public void createFrame(){
        createTopPanel();
        createMiddlePanel();
        createBottomPanel();
        setMinimumSize(new Dimension(icon.getIconWidth(), icon.getIconHeight())); // 设置最小窗口

        JPanel panelContainer = new JPanel();
        panelContainer.setLayout(new GridBagLayout());

        GridBagConstraints c1 = new GridBagConstraints();
        c1.gridx = 0;
        c1.gridy = 0;
        c1.weightx = 0;
        c1.weighty = 1.0;
        c1.fill = GridBagConstraints.BOTH;
        panelContainer.add(topPanel, c1);

        GridBagConstraints c2 = new GridBagConstraints();
        c2.gridx = 0;
        c2.gridy = 1;
        c2.weightx = 1.0;
        c2.weighty = 1.0;
        c2.fill = GridBagConstraints.HORIZONTAL;
        panelContainer.add(middlePanel, c2);

        GridBagConstraints c3 = new GridBagConstraints();
        c3.gridx = 0;
        c3.gridy = 2;
        c3.weightx = 1.0;
        c3.weighty = 0;
        c3.fill = GridBagConstraints.HORIZONTAL;
        // 加入 bottomPanel
        panelContainer.add(bottomPanel, c3);

        setContentPane(panelContainer);
    }

    /**
     * 上面部分
     */
    public void createTopPanel(){
        icon = new ImageIcon("../img/hamming.png");
        JLabel label = new JLabel(icon);
        topPanel.add(label);
    }

    /**
     * 中间部分
     */
    public void createMiddlePanel(){

        // 采用水平布局
        middlePanel.setLayout(new BoxLayout(middlePanel, BoxLayout.X_AXIS));
        middlePanel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));

        // 创建最左边画板
        JPanel leftJPanel = new JPanel();      
        leftJPanel.setLayout(new BoxLayout(leftJPanel, BoxLayout.Y_AXIS));      // 采用垂直布局
        leftJPanel.setBorder(BorderFactory.createTitledBorder("发送端"));

        leftJPanel.add(Box.createVerticalStrut(20)); // 添加空白
        JLabel inputJLabel = new JLabel("数据(二进制)：");
        inputJLabel.setAlignmentX(Component.LEFT_ALIGNMENT);
        leftJPanel.add(inputJLabel);
        leftJPanel.add(Box.createVerticalStrut(10)); // 添加空白

        inputCode = new JTextField(10); // 输入数据
        inputCode.setAlignmentX(Component.LEFT_ALIGNMENT);
        leftJPanel.add(inputCode);

        leftJPanel.add(Box.createVerticalStrut(30));        // 添加空白

        JLabel hammingLabel1 = new JLabel("正确海明码：");
        hammingLabel1.setAlignmentX(Component.LEFT_ALIGNMENT);
        leftJPanel.add(hammingLabel1);

        leftHamming = new JTextField(10); // 显示hamming编码
        leftHamming.setEditable(false);
        leftHamming.setAlignmentX(Component.LEFT_ALIGNMENT);
        leftJPanel.add(leftHamming);
        leftJPanel.add(Box.createVerticalStrut(30)); // 添加空白

        // 添加最左边 Panel 到 middlePanel
        middlePanel.add(leftJPanel);

        // 添加中间 Panel
        JPanel centerPanel = new JPanel();
        centerPanel.setLayout(new BoxLayout(centerPanel, BoxLayout.Y_AXIS));    // 采用垂直布局
        centerPanel.setBorder(BorderFactory.createTitledBorder("信道"));

        randomError = new JButton("随机产生一位差错");
        randomError.setBorder(BorderFactory.createRaisedBevelBorder());
        randomError.setBackground(Color.CYAN);
        randomError.setAlignmentX(Component.LEFT_ALIGNMENT);
        centerPanel.add(randomError);

        JLabel label0 = new JLabel("错误码：");
        label0.setAlignmentX(Component.LEFT_ALIGNMENT);
        centerPanel.add(label0);
        errorCode = new JTextField(10);      // 产生差错后的海明码
        errorCode.setEditable(false);
        errorCode.setAlignmentX(Component.LEFT_ALIGNMENT);
        centerPanel.add(errorCode);

        outError = new JTextField(10); // 产生差错后的海明码
        outError.setEditable(false);
        outError.setAlignmentX(Component.LEFT_ALIGNMENT);
        centerPanel.add(outError);

        centerPanel.add(Box.createVerticalStrut(20)); // 添加空白

        JLabel label1 = new JLabel("正确的海明码：");
        label1.setAlignmentX(Component.LEFT_ALIGNMENT);
        centerPanel.add(label1);

        middleHamming = new JTextField(10);   // 正确的海明码
        middleHamming.setAlignmentX(Component.LEFT_ALIGNMENT);
        middleHamming.setEditable(false);
        centerPanel.add(middleHamming);
        centerPanel.add(Box.createVerticalStrut(30)); // 添加空白

        middlePanel.add(centerPanel);

        /**
         * 右边部分
         */
        JPanel rightPanel = new JPanel();
        rightPanel.setLayout(new BoxLayout(rightPanel, BoxLayout.Y_AXIS)); // 采用垂直布局
        rightPanel.setBorder(BorderFactory.createTitledBorder("接收端"));

        rightPanel.add(Box.createVerticalStrut(20)); // 添加空白
        JLabel receiveLabel = new JLabel("数据：");
        receiveLabel.setAlignmentX(Component.LEFT_ALIGNMENT);
        rightPanel.add(receiveLabel);

        rightPanel.add(Box.createVerticalStrut(10)); // 添加空白
        outputCode = new JTextField(10); // 接收端数据
        outputCode.setEditable(false);
        outputCode.setAlignmentX(Component.LEFT_ALIGNMENT);
        rightPanel.add(outputCode);

        rightPanel.add(Box.createVerticalStrut(30)); // 添加空白

        JLabel hammingLabel2 = new JLabel("待验证的海明码：");
        hammingLabel2.setAlignmentX(Component.LEFT_ALIGNMENT);
        rightPanel.add(hammingLabel2);

        rightErrorHamming = new JTextField(10); // 显示hamming编码
        rightErrorHamming.setEditable(false);
        rightErrorHamming.setAlignmentX(Component.LEFT_ALIGNMENT);
        rightPanel.add(rightErrorHamming);

        rightPanel.add(Box.createVerticalStrut(30)); // 添加空白

        middlePanel.add(rightPanel);
    }

    public void createBottomPanel(){
        bottomPanel.setLayout(new FlowLayout()); // 采用水平布局

        sendButton = new JButton("发送"); // 发送
        sendButton.setPreferredSize(new Dimension(150, 30));
        bottomPanel.add(sendButton);

        bottomPanel.add(Box.createHorizontalStrut(20));

        JLabel myName = new JLabel("计科1703-张俊峰-2017040330");
        bottomPanel.add(myName);

        bottomPanel.add(Box.createHorizontalStrut(20));

        checkButton = new JButton("检错");  // 检错
        checkButton.setPreferredSize(new Dimension(150, 30));
        bottomPanel.add(checkButton);
    }

    private static final int DEFAULT_LENGTH = 600;
    private static final int DEFAULT_WIDTH = 500;

    public Dimension getPreferredSize() {
        return new Dimension(DEFAULT_LENGTH, DEFAULT_WIDTH);
    }
}