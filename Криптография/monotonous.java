
public class monotonous3
{
    public static  String alphU ="АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ";
    public static  String alphD ="абвгдеёжзийклмнопрстуфхцчшщьыъэюя";

    public static void main(String[] args)
    {
        String strText = "Карл у Клары украл кораллы";
        String strCipher = "";
        strText = strText.replaceAll("\\s+","");//убираем пробелы
        int temp, N=8, Y=5;

        for(int i = 0; i < strText.length(); i++)
        {
            temp = find(strText.charAt(i));

            if(i%2==0)//проверка на четность
            {
                if(temp+Y > alphU.length()) temp = temp - alphU.length();
                strCipher = strCipher+alphU.charAt(temp+Y);
            }else{
                if(temp+N > alphU.length()) temp = temp - alphU.length();
                strCipher = strCipher+alphU.charAt(temp+N);
            }
        }
        System.out.println(strCipher);

        strText="";
        for(int i = 0; i < strCipher.length(); i++)
        {
            temp = find(strCipher.charAt(i));

            if(i%2==0)//проверка на четность
            {
                if(temp-Y < 0) temp = alphU.length()+temp;
                strText= strText+alphU.charAt(temp-Y);
            }else{
                if(temp-N < 0) temp = alphU.length()+temp;
                strText = strText+alphU.charAt(temp-N);
            }
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
