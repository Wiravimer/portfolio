//cls && javac -encoding UTF-8 DES.java && java DES


//import java.math.BigInteger;
//import java.util.Random;
import java.util.ArrayList;

	//System.out.println(Integer.toString(a, 2));//из 10сс в 2сс в виде строки
	//System.out.println(Integer.toBinaryString(i));//бинарное предсталение числа
	//int x = Integer.parseInt("01001", 2); X буден равен 9
	//Integer.parseInt("10")//из строки в число 
	//str.charAt(i)//показать символ по индексу
	//.getBytes();
	//str =  String.join(" ", args);//массив строк в строку через пробел
	//System.out.format("\n %02d (%02d) %c %08d", i+1, (int)str.charAt(i)-1039, str.charAt(i), Integer.parseInt(Integer.toString((int)str.charAt(i)-1039, 2)));
	//.length();//длина строки
public class DES
{
	

//PC-1 (Матрица Начальной мерестановки)
    private static int[]  IP = {
            58, 50, 42, 34, 26, 18, 10, 2,
            60, 52, 44, 36, 28, 20, 12, 4,
            62, 54, 46, 38, 30, 22, 14, 6,
            64, 56, 48, 40, 32, 24, 16, 8,
            57, 49, 41, 33, 25, 17,  9, 1,
            59, 51, 43, 35, 27, 19, 11, 3,
            61, 53, 45, 37, 29, 21, 13, 5,
            63, 55, 47, 39, 31, 23, 15, 7
    };

 //Таблица, определяющая функцию расширения.    
    private static int[] E = {
            32,  1,  2,  3,  4,  5,
            4,  5,  6,  7,  8,  9,
            8,  9, 10, 11, 12, 13,
            12, 13, 14, 15, 16, 17,
            16, 17, 18, 19, 20, 21,
            20, 21, 22, 23, 24, 25,
            24, 25, 26, 27, 28, 29,
            28, 29, 30, 31, 32,  1
    };
   
// Матрица первоначальной обработки ключа
    private static int[] G = {
            57, 49, 41, 33, 25, 17, 9,
            1, 58, 50, 42, 34, 26, 18,
            10, 2, 59, 51, 43, 35, 27,
            19, 11, 3, 60, 52, 44, 36,
            63,55, 47, 39, 31, 23, 15,
            7, 62, 54, 46, 38, 30, 22,
            14, 6, 61, 53, 45, 37, 29,
            21, 13, 5, 28, 20, 12,  4
    };

//Массив сдвигов для вычисления ключа.
    private static int[] SHIFT = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

//Матрица заверщающей обработки ключа
    private static int[] H = {
            14, 17, 11, 24, 1, 5,
            3, 28, 15, 6, 21, 10,
            23, 19, 12, 4, 26, 8,
            16, 7, 27, 20, 13, 2,
            41, 52, 31, 37, 47, 55,
            30, 40, 51, 45, 33, 48,
            44, 49, 39, 56, 34, 53,
            46, 42, 50, 36, 29, 32
    };

//Функции преобразования S1, S2, S3,..., S8
    private static int[][][] Sbox = {
            {
                    { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
                    { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
                    { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
                    { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 } },
            { 
                    { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
                    { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
                    { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
                    { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 } },
            { 
                    { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
                    { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
                    { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
                    { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 } },
            { 
                    { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
                    { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
                    { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
                    { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 } },
            { 
                    { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
                    { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
                    { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
                    { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 } },
            { 
                    { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
                    { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
                    { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
                    { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 } },
            { 
                    { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
                    { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
                    { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
                    { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 } },
            { 
                    { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
                    { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
                    { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
                    { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } }
    };

 //Таблица, определяющая функцию перестановки
    private static int[] P = {
            16, 7, 20, 21,
            29, 12, 28, 17,
            1, 15, 23, 26,
            5, 18, 31, 10,
            2, 8, 24, 14,
            32, 27, 3, 9,
            19, 13, 30, 6,
            22, 11, 4, 25
    };

  //PC-2 (Матрица обратной мерестановки)
    private static int[] IP_REVERS = {
            40, 8, 48, 16, 56, 24, 64, 32,
            39, 7, 47, 15, 55, 23, 63, 31,
            38, 6, 46, 14, 54, 22, 62, 30,
            37, 5, 45, 13, 53, 21, 61, 29,
            36, 4, 44, 12, 52, 20, 60, 28,
            35, 3, 43, 11, 51, 19, 59, 27,
            34, 2, 42, 10, 50, 18, 58, 26,
            33, 1, 41, 9,  49, 17, 57, 25,
    };
   public static void main(String[] args)//считываем из консоли
	{
		
		ArrayList<Integer> in64bit = new ArrayList<Integer>();
		ArrayList<Integer> leftOld = new ArrayList<Integer>();
		ArrayList<Integer> leftNew = new ArrayList<Integer>();
		ArrayList<Integer> right = new ArrayList<Integer>();
			
		ArrayList<Integer> key = new ArrayList<Integer>();
		ArrayList<Integer> C = new ArrayList<Integer>();
		ArrayList<Integer> D = new ArrayList<Integer>();
		
		String strText = "МАЛЫШЕВГ"; String keyText = "АЛЕКСАНД";
			
		System.out.println("Открытый текст: "+strText);
		for(int i = 0; i<strText.length(); i++)
		System.out.format("\n %02d (%02d) %c %s", i+1, (int)strText.charAt(i)-848, strText.charAt(i), Integer.toString((int)strText.charAt(i)-848,2));
		
		System.out.println("\n\nФормирование блока текста");
		in64bit = strToBit(strText);	bitPrint(in64bit, 4,"Text");
		
		in64bit = reshuffleBits(in64bit, IP);		bitPrint(in64bit,4,"PC1");
		
		for(int i = 0; i<32; i++) leftOld.add(in64bit.get(i)); bitPrint(leftOld, 4,"L");
		for(int i = 32; i<64; i++) right.add(in64bit.get(i)); bitPrint(right,4,"R");
		
		leftNew = right;
		right = reshuffleBits(right, E); bitPrint(right, 6, "E");
		
		
		System.out.println("\nКлюч: "+keyText);
		for(int i = 0; i<keyText.length(); i++)
		System.out.format("\n %02d (%02d) %c %s", i+1, (int)keyText.charAt(i)-848, keyText.charAt(i), Integer.toString((int)keyText.charAt(i)-848,2));

		System.out.println("\n\nФормирование ключа");
		key = strToBit(keyText);	bitPrint(key,8,"Key");
		
		//По заданию
		//key = reshuffleBits(key, G);	bitPrint(key, 4, "G");
		
		// for(int i = 0; i<28; i++) C.add(key.get(i)); bitPrint(C, 4, "\nC");
		// C = rightShiftBits(C,SHIFT[0]);bitPrint(C, 4, "shift C");
		
		// for(int i = 28; i<56; i++) D.add(key.get(i)); bitPrint(D, 4, "\nD");
		// D = rightShiftBits(D,SHIFT[0]);bitPrint(D, 4, "shift D");
		
		// key = gatherBits(C,D); bitPrint(key, 4, "\nKey");
		// key = reshuffleBits(key, H); bitPrint(key, 4, "H");
		
		//По примеру
		ArrayList<Integer> key48 = new ArrayList<Integer>();
		ArrayList<Integer> keyRound = new ArrayList<Integer>();
		key48 = bits64in48(key); bitPrint(key48, 6, "Key48");
		
		
		right = xor(right, key48); bitPrint(right, 6 ,"\nXOR");
		
		System.out.println("\nПриобразование S");
		right = functionS(right);bitPrint(right, 4, "S");
		right = reshuffleBits(right, P);bitPrint(right, 4 ,"P");
		right = xor(right, leftOld); bitPrint(right,4 ,"\nXOR");
		in64bit = gatherBits(leftNew, right); bitPrint(in64bit,4, "\nText");
		in64bit = reshuffleBits(in64bit, IP_REVERS);bitPrint(in64bit, 4, "PC2");
		
		System.out.println();
		bitPrint(in64bit,8,"Otvet");
		
		//for(int i=0;i<64;i++){in64bit = rightShiftBits(in64bit,i);  System.out.printf("%2d",i); bitPrint(in64bit,0,"shift");}
		
	System.out.println();
   }//main 
   
 public static ArrayList<Integer>  functionS(ArrayList<Integer> bits)
 {
	 ArrayList<Integer> box = new ArrayList<Integer>();
	 int nRow, nCol;
	 String temp1 = "", temp2 = "", strbit;

	bitPrint(bits, 6, "In");
		for(int nBox=0; nBox<8; nBox++)//определяем сколько блоков по 6 бит
		{	for(int n=0; n<6; n++){box.add(bits.get(0));bits.remove(0);}//делаем блок по 6 бит
		
		//по битам находим десятичное число
			nRow = Integer.parseInt(box.get(0)+""+box.get(5), 2);//для строки
			nCol = Integer.parseInt(box.get(1)+""+box.get(2)+box.get(3)+""+box.get(4), 2);//для столбца

			strbit=  Integer.toString(Sbox[nBox][nRow][nCol], 2); //из 10сс в 2сс в виде строки
			temp2 = temp2 +strbit;//к пустой строке добавляеться найденые биты
			for(int j=0; j<4-strbit.length(); j++)//определяет сколько битов надо дописать
				temp2 = 0+temp2;//добавляем оствшийся биты
				//System.out.println(nBox+" : "+nRow+" : "+nCol +" : "+Sbox[nBox][nRow][nCol]+" : "+temp2);
				System.out.printf("%d) %d:%-2d = %02d -> %2s\n",nBox+1,nRow,nCol,Sbox[nBox][nRow][nCol],temp2);
			temp1 = temp1+temp2;//получинный блок добавляем к основнуму числу
			
			//очищаем блок
			temp2="";
			box.clear();
		}
		System.out.println();
	for(int i = 0; i<32; i++) bits.add(Integer.parseInt(temp1.charAt(i)+""));//добавляем к основнуму числу
		return bits;
}

public static ArrayList<Integer> bits64in48(ArrayList<Integer> keyOld)
{
	       ArrayList<Integer> keyNew = new ArrayList<Integer>();

        for(int i=0,  n = 0; i<keyOld.size(); i++)
            if (n < 7){ keyNew.add(keyOld.get(i));n++;}
            else n = 0;

        bitPrint(keyNew, 8, "Key56");
        keyOld = (ArrayList)keyNew.clone();
        keyNew.clear();

        for(int i=0,  n = 0; i<keyOld.size(); i++)
            if (n < 7){ keyNew.add(keyOld.get(i));n++;}
            else n = 0;

        keyNew.remove(keyNew.size()-1);
        //bitPrint(keyNew, 6, "KeyNew48");
        return keyNew;
}

public static ArrayList<Integer> xor (ArrayList<Integer> bits1, ArrayList<Integer> bits2)// операция XOR
{
	ArrayList<Integer> tmp = new ArrayList<Integer>();
		for(int i = 0; i < bits2.size(); i++)
			if(bits1.get(i) == bits2.get(i)) tmp.add(0);
			else tmp.add(1);			
	return tmp;
}

public static ArrayList<Integer> gatherBits(ArrayList<Integer> bits1, ArrayList<Integer> bits2) //соеденение 2х блоков
{
	for(int i = 0; i < bits2.size(); i++)bits1.add(bits2.get(i));
	return bits1;
}

public static ArrayList<Integer>  rightShiftBits (ArrayList<Integer> bits, int offset)//циклический сдвиг
{
		int tmp;
		for(int i=0; i<offset; i++)
		{ 
			tmp = bits.get(0);
			bits.remove(0); 
			bits.add(tmp);
		} 
		return bits;
}

public static void bitPrint(ArrayList<Integer> bits, int num, String str)//вывод битов
{ 
int tmp=0;
	System.out.print(str+": ");
	for(int i = 0; i<bits.size(); i++)
	{
		tmp++;
		System.out.print(bits.get(i));
		if(num == tmp){System.out.print(' '); tmp=0;}
	}
	
	System.out.print(":"+bits.size()+" bit\n");
}

	public static ArrayList<Integer> reshuffleBits(ArrayList<Integer> bitsSequence, int[] table)//перемешивает биты по заданной таблицей
	{
		ArrayList<Integer> tmp = new ArrayList<Integer>();
		for(int i = 0; i<table.length; i++)	tmp.add(bitsSequence.get(table[i]-1));
		//for(int i = 0; i<tmp.size(); i++) bitsSequence.get(i) = tmp.get(i);
		return tmp;
	}		
   
   public static ArrayList<Integer> strToBit (String str)//переводит строку в биты (64) по assci порядку
   {	
	   ArrayList<Integer> bit = new ArrayList<Integer>();
	   	String temp1 = "", temp2 = "", bits;
		
		
		for(int i = 0; i<str.length(); i++)
		{
			//bits =  Integer.toString(find(str.charAt(i)), 2); //из 10сс в 2сс в виде строки по алфавиту
			bits =  Integer.toString((int)str.charAt(i)-848, 2); //из 10сс в 2сс по коду асски
			temp2 = temp2 +bits;//к пустой строке добавляеться найденые биты
			for(int j=0; j<8-bits.length(); j++)//определяет сколько битов надо дописать
				temp2 = 0+temp2;//добавляем оствшийся биты
			temp1 = temp1+temp2;//получинный блок добавляем к основнуму числу
			temp2="";//очищаем блок
		}
		
			for(int i = 0; i<str.length()*8; i++) bit.add(Integer.parseInt(temp1.charAt(i)+""));//разбивай блок битов на отдельные биты в видед числа
		return bit;
   }
   
   	// public static  int find(char symbol)//возвращает порядковый номер в алфавите
// {
	// String alph ="АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ";
	// for(int i = 0; i < alph.length(); i++)
		// if(symbol == alph.charAt(i))
			// return i+1;
	// return -1;
// }
   
}//DES