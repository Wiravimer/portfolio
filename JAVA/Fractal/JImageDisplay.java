import javax.swing.*;
import java.awt.image.*;
import java.awt.*;
class JImageDisplay extends JComponent
{
    private BufferedImage ImageIcon;
    public JImageDisplay(int width, int height) // конструктор
    {
        ImageIcon = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        Dimension imageDimension = new Dimension(width, height);// создает обьект определеной высоты и ширены
        super.setPreferredSize(imageDimension); // устонавливает препочтительный размер
    }

    @Override// вставить код из задания
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        g.drawImage(ImageIcon, 0, 0, getWidth(), getHeight(), null);
    }

    public void clearImage()
    {
        Graphics g = ImageIcon.getGraphics();
        g.clearRect(0, 0, getWidth(), getHeight());
    }

    public void drawPixel(int x, int y, int rgbColor)
    {
        ImageIcon.setRGB(x, y, rgbColor);
    }
}