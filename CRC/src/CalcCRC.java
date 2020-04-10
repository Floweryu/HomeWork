import java.math.BigInteger;

public class CalcCRC {

    /**
     * 计算冗余码
     */
    public String calcRedundancy(String dataStr, String gxStr) {

        int dataStrLength = dataStr.length(); // 二进制数据长度
        int gxStrLength = gxStr.length(); // 多项式长度 (实际添加长度时要减一)
        int sumLength = dataStrLength + gxStrLength - 1; // 二进制补 0 后的位数

        // 将字符串转换为二进制存储
        int data = Integer.valueOf(dataStr, 2);
        int gx = Integer.valueOf(gxStr, 2);

        // 补齐数据和多项式的位数
        data <<= (gxStrLength - 1);
        gx <<= (dataStrLength - 1);

        BigInteger bigData = new BigInteger("2");
        int flag = bigData.pow(sumLength - 1).intValue(); // 求取 data 的数值

        for (int i = 0; i < dataStrLength; i++) {
            if ((data & flag) != 0) { // 补零后最高位非0
                // 每次做除法就相当于 data 做除法那一部分直接和多项式异或，更新 data 的数值，然后下一步就用新的 data 值
                data ^= gx;
                gx >>= 1;
            } else {
                gx >>= 1;
            }
            flag >>= 1; // 最高位向右移1位
        }

        String redundancy = Integer.toBinaryString(data);

        // 若高位不足用 0 代替
        while (redundancy.length() < (gxStrLength - 1)) {
            redundancy = "0" + redundancy;
        }

        return redundancy;
    }

    /**
     * 判断是否出错
     */
    public boolean checkoutError(String crcStr, String gxStr){

        // 将字符串转换为二进制存储
        int data = Integer.valueOf(crcStr, 2);
        int gx = Integer.valueOf(gxStr, 2);

        int crcLength = crcStr.length();
        int gxStrLength = gxStr.length();
        int dataLength = crcLength - gxStrLength;
        gx <<= dataLength;

        BigInteger bigData = new BigInteger("2");
        int flag = bigData.pow(crcLength - 1).intValue(); // 求取 data 的数值

        for (int i = 0; i < dataLength; i++) {
            if ((data & flag) != 0) { // 补零后最高位非0
                // 每次做除法就相当于 data 做除法那一部分直接和多项式异或，更新 data 的数值，然后下一步就用新的 data 值
                data ^= gx;
                gx >>= 1;
            } else {
                gx >>= 1;
            }
            flag >>= 1; // 最高位向右移1位
            // System.out.println(Integer.toBinaryString(flag));
            // System.out.println(Integer.toBinaryString(data));
            // System.out.println(Integer.toBinaryString(gx));
            // System.out.println();
        }

        if (data == 0)
            return true;
        else
            return false;
    }

    /**
     * 二进制字符串转为十六进制
     */
    public String toHexString(String binaryString){
        int binaryLength = binaryString.length();
        int newLength;
        String newbinary = "";
        // 开头补0
        if (binaryLength % 4 != 0){
            newLength = (binaryLength / 4 + 1) * 4;
            int length = newLength - binaryLength;

            while (length > 0) {
                newbinary += "0";
                length--;
            }
        }
        binaryString = newbinary + binaryString;

        String hexString = "";
        for (int i = 0; i < binaryString.length(); i += 4){
            String four = binaryString.substring(i, i + 4);
            int data = Integer.valueOf(four, 2);
            String hex = Integer.toHexString(data);
            hexString += hex;
        }
        return hexString;
    }

}