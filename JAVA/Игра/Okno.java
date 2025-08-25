import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;// представляет собой генератор псевдослучайных чисел
import java.util.ArrayList;// автоматически расширяемый массив
import java.io.*;


public class Okno extends JFrame//Наследуя от JFrame мы получаем всю функциональность окна
{ 
    private int lvl = 0;
    private int usr = -1;
    private JFrame frame;
    private JLabel balanceLabel;
    private JPanel gamePanel;
    private JPanel btnPanel;
    private JPanel menuPanel;
    private JPanel ratingPanel;
    private JPanel endPanel;
    private JButton start;
    private JButton exit;
    private JButton rating;
    private JButton yes;
    private JButton no;
    private JButton menu;
    private JButton btn1;
    private JButton btn2;
    private JButton btn3;
    private JButton btn4;
    private JTextArea ratingTextArea;
    private JTextField txtField;
    
    private Rating file = new Rating();
    
    
    private ArrayList<Integer> listLvl = new ArrayList<>();
    private ArrayList<Integer> listUsr = new ArrayList<>();
 
    
    public Okno()
    {
        //file.addTxt("222");
        //file.addTxt("111");
       
        //Создаем фрейм (окно)
        frame = new JFrame("Game");
        
        //Просим программу закрыться при закрытии фрейма, иначе она останется висеть в процессах
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        menuPanel = new JPanel();
        //menuPanel.setPreferredSize(new Dimension(200, 220));
        //menuPanel.setLayout(new BoxLayout(menuPanel, BoxLayout.Y_AXIS));
        //menuPanel.setBorder(BorderFactory.createLineBorder(Color.yellow));
        frame.add(menuPanel);  
        start = new JButton("Start");menuPanel.add(start);
        rating = new JButton("Rating");menuPanel.add(rating);
        exit = new JButton("Exit");menuPanel.add(exit);      
                
        ratingPanel = new JPanel();
        ratingPanel.setLayout(new BoxLayout(ratingPanel, BoxLayout.Y_AXIS));  
        ratingTextArea = new JTextArea();
        ratingTextArea.setEditable(false);ratingPanel.add(ratingTextArea);
        menu= new JButton("Menu");ratingPanel.add(menu);
      
        gamePanel = new JPanel();
        gamePanel.setLayout(new BoxLayout(gamePanel, BoxLayout.Y_AXIS));  
        btnPanel = new JPanel(new GridLayout(2,2));//панель с табличным расположением
 
        endPanel = new JPanel();
        endPanel.setLayout(new BoxLayout(endPanel, BoxLayout.Y_AXIS));
        JLabel  endLabel1 = new JLabel("You made a mistake");endPanel.add(endLabel1);
        JLabel  endLabel2 = new JLabel("Save the result?");endPanel.add(endLabel2);
        JLabel  endLabel3 = new JLabel("Name: ");endPanel.add(endLabel2);
        txtField  = new JTextField(10); endPanel.add(txtField);
        JPanel endPanel1 = new JPanel();endPanel.add(endPanel1);
        endPanel1.add(endLabel3);
        endPanel1.add(txtField);
        JPanel endPanel2 = new JPanel();endPanel.add(endPanel2);
        yes = new JButton("Yes");endPanel2.add(yes);
        no = new JButton("No"); endPanel2.add(no);
        
        
        //Создадим лейбл и поместим его
        balanceLabel = new JLabel("LVL: " + lvl);
        gamePanel.add(balanceLabel);
        
        btn1 = new JButton();//Создадим кнопку
        btn1.setBackground(Color.BLUE);//меняем цвет на синий
        btn1.setPreferredSize(new Dimension(100, 100));//задаем размер
        btnPanel.add(btn1);//поместим  в панель
        
        btn2 = new JButton();
        btn2.setBackground(Color.GREEN);
        btnPanel.add(btn2);
        
        btn3 = new JButton();
        btn3.setBackground(Color.RED);
        btnPanel.add(btn3);
        
        btn4 = new JButton();
        btn4.setBackground(Color.YELLOW);
        btnPanel.add(btn4);       
             
        gamePanel.add(btnPanel, BorderLayout.SOUTH);

  
                    start.addActionListener(new ActionListener()
                    {
                        public void actionPerformed(ActionEvent e) 
                        {
                            frame.remove(menuPanel);
                            frame.add(gamePanel, BorderLayout.CENTER);
                            frame.pack();
                            frame.repaint();
                            next();
                            //start.setVisible(false);
                        }
                    });
                    
                    exit.addActionListener(new ActionListener()
                    {
                        public void actionPerformed(ActionEvent e) 
                        {
                            System.exit(0);
                        }
                    });
                    
                    rating.addActionListener(new ActionListener()
                    {
                        public void actionPerformed(ActionEvent e) 
                        {
                            frame.remove(menuPanel);
                            frame.add(ratingPanel, BorderLayout.CENTER);
                            ratingTextArea.setText(null);
                            file.readTxt();
                            for(int i = 0; i<10 && i<file.sizeRating(); i++)
                            {
                                //String.valueOf(n)+" "+String.valueOf(file.getRating(i)) +"\n"
                                //ratingTextArea.append(file.getRating(i)+"\n");
                                ratingTextArea.append(String.valueOf(i+1 + "->")+" "+String.valueOf(file.getRating(i)) +"\n");
                                //ratingTextArea.append(String.valueOf(i+1) +"\n");
                                //System.out.print(file.getRating(i)+"\n");
                            }
                            frame.pack();
                            frame.repaint();
                        }
                    });
            
                    menu.addActionListener(new ActionListener()
                    {
                        public void actionPerformed(ActionEvent e) 
                        {
                            frame.remove(ratingPanel);
                            frame.add(menuPanel);
                            frame.pack();
                            frame.repaint();
                        }
                    });
                    
                    yes.addActionListener(new ActionListener()
                    {
                        public void actionPerformed(ActionEvent e) 
                        {
                            file.addTxt( lvl+" "+txtField.getText() );
                            txtField.setText("");
                            frame.remove(endPanel);
                            frame.add(menuPanel);
                            frame.pack();
                            frame.repaint();
                            listLvl.clear();
                            listUsr.clear();
                            lvl=0; usr=-1;  
                        }
                    });
                    
                    no.addActionListener(new ActionListener()
                    {
                        public void actionPerformed(ActionEvent e) 
                        {
                            listLvl.clear();
                            listUsr.clear();
                            lvl=0; usr=-1;  
                            frame.remove(endPanel);
                            frame.add(menuPanel);
                            frame.pack();
                            frame.repaint();
                        }
                    });
                    
                   //Добавим к кнопке слушатель события
                    btn1.addActionListener(new ActionListener()
                    {
                        public void actionPerformed(ActionEvent e) 
                        {
                            usr++;
                            listUsr.add(1);
                            proverka();
                        }
                    });
                                       
                    btn2.addActionListener(new ActionListener()
                    {public void actionPerformed(ActionEvent e) {usr++;listUsr.add(2);proverka();}});
                                        
                     btn3.addActionListener(new ActionListener()
                    {public void actionPerformed(ActionEvent e) {usr++;listUsr.add(3);proverka();}});
                                                            
                     btn4.addActionListener(new ActionListener()
                    {public void actionPerformed(ActionEvent e) {usr++;listUsr.add(4);proverka();}});
 
                     
                    
                 
        frame.pack();//Установка размеров окна в зависимости от содержимого
        frame.setVisible(true);//Показать фрейм
        frame.setResizable(false);// заприщает изменения размера окна
        AllSetEnable(false);
        
    }   
 
       
     private void AllSetEnable(boolean parametr) 
     {
         btn1.setEnabled(parametr);
         btn2.setEnabled(parametr);
         btn3.setEnabled(parametr);
         btn4.setEnabled(parametr);
     }
     
     private void pause(int time)
     {
        try 
           {
               Thread.sleep(time);// пауза
           } 
           catch (InterruptedException e) {} 
     }
     
     public  void addLvl()//добаляем еще один цвет для нового уровня
     { 
         lvl++;
         balanceLabel.setText("LVL: " + lvl);//Обновляем содержимое Лейбла
         listLvl.add(random());
     }
     
     public  int random()//рандом от 1 до 4
     {
        // return (int) (Math.random() * 4)+ 1;
        Random r = new Random();
        int x = r.nextInt(4) + 1;
        return x;
     }
     
    public  void startLvl() 
     {
         int tmp;
         pause(500);
         //balanceLabel.setText("Запомни");
         AllSetEnable(false);//отключаем взаимодействие с кнопками
          for(int index=0; index<listLvl.size();index++) //для перебора всех уровней
        {
            tmp = listLvl.get(index);
            pause(500);
            blinkСolor (tmp);
        }
         AllSetEnable(true);//включаем взаимодействие с кнопками
         pause(500);
         //balanceLabel.setText("Повтори");
     }

      private void blinkСolor (int color) 
     {
            if(color == 1)
            {
                btn1.setVisible(false);
                pause(500);
                btn1.setVisible(true);
            }
            else if(color == 2)
            {
                btn2.setVisible(false);
                pause(500);
                btn2.setVisible(true);
            }
             else if(color == 3)
            {
                btn3.setVisible(false);
                pause(500);
                btn3.setVisible(true);
            }
             else if(color == 4)
            {
                btn4.setVisible(false);
                pause(500);
                btn4.setVisible(true);
            }
     }
     
   public void proverka()
    {    
           if(listLvl.get(usr) == listUsr.get(usr)) 
           {
               //balanceLabel.setText("Правильно");
               if(listLvl.size() == listUsr.size()) {next();listUsr.clear();usr=-1;}
           } 
           else
           {
               //AllSetEnable(false);
               //balanceLabel.setText("Wrong");
              // start.setText("Restart");
              //start.setVisible(true);
               frame.remove(gamePanel);
               frame.add(endPanel);
               frame.pack();
               frame.repaint();
           } 
           
    }
     
     public void next()
     {
            addLvl();
            //startLvl();
            
            Thread myThready = new Thread(new Runnable() 
                    { 
                        public void run() //Этот метод будет выполняться в побочном потоке 
                        { 
                            startLvl() ;  
                        } 
                    });
                    myThready.start(); //Запуск потока
     }
     
     
     
     
  public static void main(String[] args)
  { 
    Okno app = new Okno(); //Создаем экземпляр приложения
  }
      
}






























//public class Okno extends JFrame//Наследуя от JFrame мы получаем всю функциональность окна
//{ 
//
//    private JFrame frame;
//    private JLabel balanceLabel;
//    private JPanel btnPanel;
//    private JPanel panel;
//    public JButton start;
//    private JButton btn1;
//    private JButton btn2;
//    private JButton btn3;
//    private JButton btn4;
//    
//   
//    public void StartFrame()
//    {
//        //Создаем фрейм (окно)
//        frame = new JFrame("Game");
//        
//        //Просим программу закрыться при закрытии фрейма, иначе она останется висеть в процессах
//        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//        
//        btnPanel = new JPanel(new GridLayout(2,2));//панель с табличным расположением
//        panel = new JPanel();
//        panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
//  
//        //Создадим лейбл и поместим его во фрейм
//        balanceLabel = new JLabel("LVL: ");
//        panel.add(balanceLabel);
//        
//        start = new JButton("Start");
//        panel.add(Box.createRigidArea(new Dimension(10,0)));//добавляем растояние между компанентами
//        panel.add(start);
//        //start.addActionListener(new ButtonListener());
//        
//        btn1 = new JButton();//Создадим кнопку
//        btn1.setBackground(Color.BLUE);//меняем цвет на синий
//        btn1.setPreferredSize(new Dimension(100, 100));//задаем размер
//        btnPanel.add(btn1);//поместим  в панель
//        
//        btn2 = new JButton();
//        btn2.setBackground(Color.GREEN);
//        btnPanel.add(btn2);
//        
//        btn3 = new JButton();
//        btn3.setBackground(Color.RED);
//        btnPanel.add(btn3);
//        
//        btn4 = new JButton();
//        btn4.setBackground(Color.YELLOW);
//        btnPanel.add(btn4);
//        
//        frame.add(panel, BorderLayout.NORTH);
//        frame.add(btnPanel, BorderLayout.SOUTH);//помести панель во фрейм
//  
//        frame.pack();//Установка размеров окна в зависимости от содержимого
//        frame.setVisible(true);//Показать фрейм
//        frame.setResizable(false);// заприщает изменения размера окна
//        AllSetEnable(false);
//        
//    }   
//       
//     private void AllSetEnable(boolean parametr) 
//     {
//         btn1.setEnabled(parametr);
//         btn2.setEnabled(parametr);
//         btn3.setEnabled(parametr);
//         btn4.setEnabled(parametr);
//     }             
//}

     
  
//            
//                   //Добавим к кнопке слушатель события
//                    btn1.addActionListener(new ActionListener()
//                    {
//                        public void actionPerformed(ActionEvent e) 
//                        {
//                            usr++;
//                            listUsr.add(1);
//                            proverka();
//                        }
//                    });
//                    
//                    btn2.addActionListener(new ActionListener()
//                    {public void actionPerformed(ActionEvent e) {usr++;listUsr.add(2);proverka();}});
//                                        
//                     btn3.addActionListener(new ActionListener()
//                    {public void actionPerformed(ActionEvent e) {usr++;listUsr.add(3);proverka();}});
//                                                            
//                     btn4.addActionListener(new ActionListener()
//                    {public void actionPerformed(ActionEvent e) {usr++;listUsr.add(4);proverka();}});
// 