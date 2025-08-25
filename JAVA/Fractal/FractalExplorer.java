import javax.swing.*;
import java.awt.*;
import java.awt.geom.Rectangle2D;
import java.awt.event.*;

    public class FractalExplorer
    {
        // переменные из задания
        private int displaySize;
        private JImageDisplay display;
        private FractalGenerator fractal;
        private Rectangle2D.Double range;

        public FractalExplorer(int size)// конструктор взят из задания
        {
            displaySize = size;
            fractal = new Mandelbrot();
            range = new Rectangle2D.Double();
            fractal.getInitialRange(range);
            display = new JImageDisplay(displaySize, displaySize);// объект отоброжения изоброжения
        }

        public void createAndShowGUI()
        {
            display.setLayout(new BorderLayout());// полярное расположение
            JFrame frame = new JFrame("Fractal Explorer");// создаёт контейнер рамка
            frame.add(display, BorderLayout.CENTER);// добовляет в рамку дисплей с расположение по центру
            JButton resetButton = new JButton("Reset Display");// создаёт кнопку
            ResetHandler handler = new ResetHandler();// создает обробочик сброса
            resetButton.addActionListener(handler);// добовляет обрабочук сбросоак кнопки
            frame.add(resetButton, BorderLayout.SOUTH);// добовляет в рамку кнопку с раположением снизу
            MouseHandler click = new MouseHandler();// создает обрабочек клика мыши
            display.addMouseListener(click);// добовляет обрабочек клика к дисплею
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// при нажатие крестика оканчивается программа
            // нужны по заданию
            frame.pack();// устонавливает минимальный размер окна для отображения всех элементов
            frame.setVisible(true);// открываем окно
            frame.setResizable(false);// заприщает изменения размера окна

        }

        private void drawFractal()
        {
            for (int x=0; x<displaySize; x++)
            {
                for (int y=0; y<displaySize; y++){
                    double xCoord = fractal.getCoord(
                            range.x, range.x + range.width, displaySize, x);// взято из задания

                    double yCoord = fractal.getCoord(
                            range.y, range.y + range.height, displaySize, y);// взято из задания

                    int iteration = fractal.numIterations(xCoord, yCoord);// связан с файлои Mandelbrot

                    if (iteration == -1) {
                        display.drawPixel(x, y, 0);

                    }
                    // взято из задание
                    else {
                        float hue = 0.7f + (float) iteration / 200f;
                        int rgbColor = Color.HSBtoRGB(hue, 1f, 1f);
                        display.drawPixel(x, y, rgbColor);

                    }
                }
            }
            // после того как все пиксели нарисованы
            display.repaint();// перерисовывает изображения
        }

        private class ResetHandler implements ActionListener
        {
            // обробочик сбрасывает диапозон до начального, а за тем рисует фрактал
            public void actionPerformed(ActionEvent e)

            {
                fractal.getInitialRange(range);
                drawFractal();
            }
        }
        // внутряний класс для оброботки события клика с дисплея
        private class MouseHandler extends MouseAdapter// внутриний класс для обработки события кнопки сброса
        {
            public void mouseClicked(MouseEvent e)
            {
                //получить координату х, области отопрожения клика
                int x = e.getX();
                double xCoord = fractal.getCoord(
                        range.x, range.x + range.width, displaySize, x);

                int y = e.getY();
                double yCoord = fractal.getCoord(
                        range.y, range.y + range.height, displaySize, y);
                fractal.recenterAndZoomRange(range, xCoord, yCoord, 0.5);
                drawFractal();// ищет фрактал заного
            }
        }

        public static void main(String[] args)// добавленно соглосно заданию
        {
            FractalExplorer displayExplorer = new FractalExplorer(500);
            displayExplorer.createAndShowGUI();
            displayExplorer.drawFractal();
        }
    }
