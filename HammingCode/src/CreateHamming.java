public class CreateHamming {

    /**
     * 计算 Hamming 编码
     * @param code
     */
    public String encodeHamming(final String code){
        // 字符形式转换成 Int 型
        int[] codeInt = new int[code.length()];
        for (int i = 0; i < code.length(); i++){
            codeInt[i] = Integer.parseInt(code.substring(i, i + 1));
        }

        int codeLength = codeInt.length;
        int checkout = verifyLength(codeLength);
        int hammingLength = codeLength + checkout;

        int[] hamming = new int[hammingLength];         // 存储Hamming码

        // 添加校验位
        for(int i = 0, j = 0, p = 0; i < hammingLength && j < codeLength; i++){
            if (Math.pow(2, p) == (i + 1) && p < checkout){ // 如果是校验位。默认设置为 0 
                hamming[i] = 0;
                p++;
            }
            else{
                hamming[i] = codeInt[j++];
            }
        }

        for (int i = 0; i < checkout; i++){
            int count = 1 << i, result = 0;
            for (int j = count - 1; j < hammingLength; j += count){
                for (int k = 0; k < count && j < hammingLength; k++){       // 可能最后不足 count 数目
                    result ^= hamming[j++];
                }
            }
            hamming[count - 1] = result;
        }

        String hammingStr = "";
        for (int each : hamming){
            hammingStr += String.valueOf(each);
        }

        return hammingStr;
    }

    /**
     * 纠错
     * @param code 带纠错码
     */
    public String getErrorIndex(final String code){
        // 字符形式转换成 Int 型
        int[] codeInt = new int[code.length()];
        for (int i = 0; i < code.length(); i++) {
            codeInt[i] = Integer.parseInt(code.substring(i, i + 1));
        }

        int codeLength = codeInt.length;
        int checkout = verifyLength(codeLength);

        StringBuffer checkCode = new StringBuffer();
        for (int i = 0; i < checkout; i++){
            int count = 1 << i, result = 0;
            for (int j = count - 1; j < codeLength; j += count){
                for (int k = 0; k < count && j < codeLength; k++){
                    result ^= codeInt[j++];
                }
            }
            checkCode.append(String.valueOf(result));
        }
        String indexStr = checkCode.reverse().toString();
        int index = Integer.valueOf(indexStr, 2);       // 得到出错位置

        String out1;
        if (index != 0){
            codeInt[index - 1] = (codeInt[index - 1] == 0) ? 1 : 0;
            out1 = "纠错后：";
        }
        else{
            out1 = "未出错：";
        }
        for (int each : codeInt) {
            out1 += String.valueOf(each);
        }
            
        return out1;
    }

    /**
     * 计算校验码的长度
     * @param codeLength    需要编码的长度
     * @return  校验码长度
     */
    public int verifyLength(int codeLength){
        int k = 1;
        while (Math.pow(2, k) - 1 < codeLength + k){
            k++;
        }
        return k;
    }
}