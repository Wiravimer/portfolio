import java.awt.geom.Rectangle2D;

    public class Mandelbrot extends FractalGenerator

    {
        public static final int MAX_ITERATIONS = 2000;// взято из задания
        public void getInitialRange(Rectangle2D.Double range)// взято из задания

        {
            range.x = -2;
            range.y = -1.5;
            range.width = 3;
            range.height = 3;
        }

        public int numIterations( double x, double y)
        {
            double zR, zI, iter;
            zR = 0;
            zI = 0;
            iter = 0;

            while (iter < MAX_ITERATIONS && zR * zR + zI * zI < 4)
            {
                double NewzR = zR * zR - zI * zI + x;
                double NewzI = 2 * zR * zI + y;
                zR = NewzR;
                zI = NewzI;
                iter = iter + 1;
            }

            if (iter == MAX_ITERATIONS)// взято из задания

            {
                return -1;// точка не выходит за граници
            }
            return (int) iter;
        }
    }