//cls && javac -encoding UTF-8 RSA.java && java RSA
import java.math.BigInteger;//для хранения больших чисел
import java.util.Random;

public class RSA 
{
    public static void main(String[] args)
    {
	String str = "HELLO";

	BigInteger p,q,n,euler,d,tmp, e = BigInteger.ONE;
	
	int bit = 8, len = str.length();

	char[] plaintext = new char[len];
	BigInteger [] cipher  = new BigInteger[len];
 
        
	 p = BigInteger.probablePrime(bit, new Random());
	 q = BigInteger.probablePrime(bit, new Random());
	 n = p.multiply(q);
	 euler = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));
                   
	for(int i = 1; i == 1;)//находим взаимно простое с  euler
	{
		e = BigInteger.probablePrime(bit, new Random());
		if(e.gcd(euler).compareTo(BigInteger.ONE) == 0) i=0;
	}
	
	d =  e.modInverse(euler);//находим обратное к е
        
        	 System.out.println("Открытый ключ: e = "+e+" n = "+n);
                  System.out.println("Закрытый ключ: d = "+d+" n = "+n);

	
        //шифрование
        System.out.print("Шифр текс: ");
	 for(int i = 0; i < len; i++)
	 {
                            tmp = BigInteger.valueOf(str.charAt(i));//конвертируем посимвольно в большое число
                            tmp = pow(tmp, e);
                            tmp = tmp.mod(n);
                            cipher[i] = tmp;
                           System.out.print(cipher[i]);
			
	 }
	 
//дешифрование
                   System.out.print("\nОткрытый текст: ");
	 for(int i = 0; i < len; i++)
	 {
                        tmp = cipher[i];
                        tmp = pow(tmp, d);
                        tmp = tmp.mod(n);
                        plaintext[i] = (char) (tmp.intValue());
                        System.out.print(plaintext[i]);
	 }

   }//main
   
	static BigInteger pow(BigInteger a, BigInteger b)//функция возвидения в степень для больших чисел
	{
		BigInteger result = BigInteger.ONE;
		for (BigInteger i = BigInteger.ZERO; i.compareTo(b) == -1; i = i.add(BigInteger.ONE)){
			result = result.multiply(a);
		}
		return result;
	}
   
}//RSA