import java.io.*;
import java.util.ArrayList;
//import java.util.*;

public class Rating
{   

    File file = new File("rating.txt");//создаеться файл в памяти , а не на диске
    private ArrayList<String> listRating = new ArrayList<>();
    //private ArrayList<Integer> listTemp = new ArrayList<>();
    
    public void addTxt(String str)
    {
        try
        {
            FileWriter fw = new FileWriter(file, true);
            BufferedWriter bw = new BufferedWriter(fw);
            bw.write(str);
            bw.newLine();
            bw.close();
         }catch(IOException e){System.out.print("ERROR ->" + e);}
    }
    
    public void readTxt()
    {
        try
        {
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);
            listRating.clear();
            while(br.ready())//проверяем до конец файла
            { System.out.println(listRating.add(br.readLine()));}//читаем построчно
            br.close();
        }catch(IOException e){System.out.print("ERROR ->" + e);}     
        
        //Collections.sort(listTemp, Collections.reverseOrder());
        sortRating();        
    }
    
    public String getRating(int i){return listRating.get(i);}
    public int sizeRating() { return listRating.size();}
    //public void clearRating(){listRating.clear();}
    public void sortRating() 
    { 
        String[] str1, str2;
        boolean iteration = true;
        while(iteration)
        {
           iteration = false;
           for(int i = 1; i<listRating.size(); i++)
           {
               str1 = listRating.get(i).split(" ");
               str2 = listRating.get(i-1).split(" ");

               if( Integer.parseInt(str1[0])> Integer.parseInt(str2[0]))
               {
                   swap(i, i-1);
                   iteration = true;
               }
           } 
        }
    }
    
            
    private void swap(int ind1, int ind2)
    {
        String tmp =listRating.get(ind1);
        listRating.set(ind1,listRating.get(ind2));
        listRating.set(ind2,tmp);   
    }
    
}
    
               
      
