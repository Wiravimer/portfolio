import java.util.ArrayList;

public class GOST
{	

private static int[][] Sbox ={
	 {1,13,4,6,7,5,14,4}, //0
	 {15,11,11,12,13,8,11,10},//1
	 {13,4,10,7,10,1,4,9},//2
	 {0,1,0,1,1,13,12,2},//3
	 {5,3,7,5,0,10,6,13},//4
	 {7,15,2,15,8,3,13,8},//5
	 {10,5,1,13,9,4,15,0},//6
	 {4,9,13,8,15,2,10,14},//7
	 {9,0,3,4,14,14,2,6},//8
	 {2,10,6,10,4,15,3,11},//9
	 {3,14,8,9,6,12,8,1},//10
	 {14,7,5,14,12,7,1,12},//11
	 {6,6,9,0,11,6,0,7},//12
	 {11,8,12,3,2,0,7,15},//13
	 {8,2,15,11,5,9,5,5},//14
	 {12,12,14,2,3,11,9,3}//15
 };
   
   public static void main(String[] args)//считываем из консоли
	{
		
		ArrayList<Integer> bitText = new ArrayList<Integer>();
		ArrayList<Integer> bitKey = new ArrayList<Integer>();
		ArrayList<Integer> bitL = new ArrayList<Integer>();
		ArrayList<Integer> bitR = new ArrayList<Integer>();
		ArrayList<Integer> bitRold = bitR;
		
		String strText = "МАЛЫШЕВГ";String strKey =   "АЛЕК";

			
		System.out.println("Открытый текст: "+strText);
		for(int i = 0; i<strText.length(); i++)
		System.out.format("\n %02d (%02d) %c %s", i+1, (int)strText.charAt(i)-848, strText.charAt(i), Integer.toString((int)strText.charAt(i)-848,2));
		
			
		bitText = strToBit(strText);	bitPrint(bitText, 4,"\n\nText");
		
		for(int i = 0; i<32; i++) bitL.add(bitText.get(i)); bitPrint(bitL, 4,"L");
		for(int i = 32; i<64; i++) bitR.add(bitText.get(i)); bitPrint(bitR,4,"R");
		
		System.out.println("\nКлюч: "+strKey);
		for(int i = 0; i<strKey.length(); i++)
		System.out.format("\n %02d (%02d) %c %s", i+1, (int)strKey.charAt(i)-848, strKey.charAt(i), Integer.toString((int)strKey.charAt(i)-848,2));
		bitKey = strToBit(strKey);		bitPrint(bitKey, 4,"\n\nKey");
		
		
		bitR = sum(bitR,bitKey); bitPrint(bitR,4,"Sum");
		
		
		bitR = functionS(bitR);bitPrint(bitR,4,"S ");
		bitR = rightShiftBits(bitR,11); bitPrint(bitR,4,"shift");
		
		//bitPrint(bitL,4,"\nL  ");
		//bitPrint(bitR,4,"R  ");
		bitR = xor(bitR,bitL); bitPrint(bitR,4,"XOR");
		bitL = bitRold;
		
		bitText = gatherBits(bitL,bitR);bitPrint(bitText,4,"Otvet");
		
	System.out.println();
   }//main
   
   public static ArrayList<Integer> gatherBits(ArrayList<Integer> bits1, ArrayList<Integer> bits2) //соеденение 2х блоков
{
	for(int i = 0; i < bits2.size(); i++)bits1.add(bits2.get(i));
	return bits1;
}
   
   public static ArrayList<Integer> xor (ArrayList<Integer> bits1, ArrayList<Integer> bits2)// операция XOR
{
	ArrayList<Integer> tmp = new ArrayList<Integer>();
		for(int i = 0; i < bits2.size(); i++)
			if(bits1.get(i) == bits2.get(i)) tmp.add(0);
			else tmp.add(1);			
	return tmp;
}
   
   public static ArrayList<Integer>  rightShiftBits (ArrayList<Integer> bits, int offset)//циклический сдвиг
{
		int tmp;
		for(int i=0; i<offset; i++)
		//for(int i=0; i<32; i++)
		{
			
			tmp = bits.get(0);
			bits.remove(0); 
			bits.add(tmp);
			//System.out.printf("%2d",i+1);bitPrint(bits,0,"");
		} 
		return bits;
}
   
   public static ArrayList<Integer>  functionS(ArrayList<Integer> bits)
 {
	 ArrayList<Integer> box = new ArrayList<Integer>();
	 int nRow, nCol;
	 String temp1 = "", temp2 = "", strbit;

		for(int nBox=0; nBox<8; nBox++)//определяем сколько блоков по 4 бит
		{	for(int n=0; n<4; n++){box.add(bits.get(0));bits.remove(0);}//делаем блок по 4 бит
		
		//по битам находим десятичное число
		nRow = Integer.parseInt(box.get(0)+""+box.get(1)+box.get(2)+""+box.get(3), 2);//для строки

			strbit=  Integer.toString(Sbox[nRow][nBox], 2); //из 10сс в 2сс в виде строки
			temp2 = temp2 +strbit;//к пустой строке добавляеться найденые биты
			for(int j=0; j<4-strbit.length(); j++)//определяет сколько битов надо дописать
				temp2 = 0+temp2;//добавляем оствшийся биты
				//System.out.println(nBox+8-nBox*2+" : "+nRow+" : "+Sbox[nRow][nBox]+" : "+temp2);
				System.out.printf("%d) %d:%-2d = %-2d -> %2s\n",nBox, nBox+8-nBox*2, nRow, Sbox[nRow][nBox], temp2);
			temp1 = temp1+temp2;//получинный блок добавляем к основнуму числу
			
			//очищаем блок
			temp2="";
			box.clear();
		}
		System.out.println();
		
	for(int i = 0; i<32; i++) bits.add(Integer.parseInt(temp1.charAt(i)+""));//добавляем к основнуму числу
		return bits;
}
   
   public static ArrayList<Integer> sum (ArrayList<Integer> bits1, ArrayList<Integer> bits2)// операция сложения по mod 2^32
{
	ArrayList<Integer> tmp = new ArrayList<Integer>();
	int transfer = 0;
		for(int i = bits2.size()-1; i >=0 ; i--)
		{
				   if (bits1.get(i) == 0 && bits2.get(i) == 0 && transfer == 0){ tmp.add(0,0); transfer=0;}
			else if (bits1.get(i) == 0 && bits2.get(i) == 0 && transfer == 1){ tmp.add(0,1); transfer=0;}
			else if (bits1.get(i) == 0 && bits2.get(i) == 1 && transfer == 0){ tmp.add(0,1); transfer=0;}
			else if (bits1.get(i) == 0 && bits2.get(i) == 1 && transfer == 1){ tmp.add(0,0); transfer=1;}
			else if (bits1.get(i) == 1 && bits2.get(i) == 0 && transfer == 0){ tmp.add(0,1); transfer=0;}
			else if (bits1.get(i) == 1 && bits2.get(i) == 0 && transfer == 1){ tmp.add(0,0); transfer=1;}
			else if (bits1.get(i) == 1 && bits2.get(i) == 1 && transfer == 0){ tmp.add(0,0); transfer=1;}
			else if (bits1.get(i) == 1 && bits2.get(i) == 1 && transfer == 1){ tmp.add(0,1);  transfer=1;}
		}
			//if(transfer==1)tmp.add(0,1);
	return tmp;
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
  
 public static ArrayList<Integer> strToBit (String str)//переводит строку в биты (64) по assci порядку
   {	
	   ArrayList<Integer> bit = new ArrayList<Integer>();
	   	String temp1 = "", temp2 = "", bits;
			
		for(int i = 0; i<str.length(); i++)
		{
			//bits =  Integer.toString(find(str.charAt(i)), 2); //из 10сс в 2сс в виде строки по алфавиту
				if((int)str.charAt(i) != 32) bits =  Integer.toString((int)str.charAt(i)-848, 2); //из 10сс в 2сс по коду асски
				else bits = Integer.toString(32, 2);
			temp2 = temp2 +bits;//к пустой строке добавляеться найденые биты
			for(int j=0; j<8-bits.length(); j++)//определяет сколько битов надо дописать
				temp2 = 0+temp2;//добавляем оствшийся биты
			temp1 = temp1+temp2;//получинный блок добавляем к основнуму числу
			temp2="";//очищаем блок
		}
		
			for(int i = 0; i<str.length()*8; i++) bit.add(Integer.parseInt(temp1.charAt(i)+""));//разбивай блок битов на отдельные биты в видед числа
		return bit;
   }
  
}//GOST