//cls && javac -encoding UTF-8 EP.java && java EP
public class polyalphabetic5
{	
    public static  String alphU ="АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ";
    public static  String alphD ="абвгдеёжзийклмнопрстуфхцчшщьыъэюя";
    public static int offset, numChar;

    public static void main(String[] args)
    {
         String strText = "КарлуКларыукралкораллы";
         String strKey  =  "ШифрШифрШифрШифрШирфШи";

        String strCipher = "";

        for(int i = 0; i < strText.length(); i++)
        {
            offset = find(strKey.charAt(i));
            numChar = find(strText.charAt(i));
            if(numChar+offset>= alphU.length()) numChar = numChar - alphU.length();
            strCipher = strCipher+alphU.charAt(numChar+offset);
        }
        System.out.println(strCipher );

         strText = "";
        for(int i = 0; i < strCipher.length(); i++)
        {
            offset = find(strKey.charAt(i));
            numChar = find(strCipher.charAt(i));
            if(numChar-offset < 0) numChar = numChar + alphU.length();
            strText = strText+alphU.charAt(numChar-offset);
        }

        System.out.println(strText);

        System.out.println();
    }//main

    public static  int find(char symbol)//возвращает порядковый номер в алфавите
    {
        for(int i = 0; i < alphU.length(); i++)
            if(symbol == alphU.charAt(i) || symbol == alphD.charAt(i))
                return i;
        return -1;
    }


}//