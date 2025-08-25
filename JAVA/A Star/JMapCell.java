
import java.awt.*;
import javax.swing.*;
import javax.swing.border.*;


/**
* Ётот класс €вл€етс€ пользовательским компонентом дл€ представлени€ одной €чейки карты в
* 2D-карта.  летка имеет несколько различных видов состо€ний, но самое основное
* состо€ние-это то, €вл€етс€ ли клетка проходимой или нет.
*/
public class JMapCell extends JComponent
{
    private static final Dimension CELL_SIZE = new Dimension(12, 12);
    
    // True указывает, что €чейка €вл€етс€ конечной точкой, либо начальной  
    boolean endpoint = false;
    
    
    //True означает, что €чейка €вл€етс€ проходимой; false означает, что это не так
    boolean passable = true;
    
    //True указывает, что эта €чейка €вл€етс€ частью пути между началом и концом
    boolean path = false;
    
    // ѕостроить новую €чейку карты с заданной "проходимостью." ¬ход  true означает, что €чейка €вл€етс€ проходимой
    public JMapCell(boolean pass)
    {
        setPreferredSize(CELL_SIZE);
        
        setPassable(pass);
    }
    
    public JMapCell()
    {
        this(true);
    }
    
    // ѕомечает эту €чейку как начальную или конечную
    public void setEndpoint(boolean end)
    {
        endpoint = end;
        updateAppearance();
    }
    
    // ”станавливает эту €чейку проходимой или не проходимой. ¬вод истинных меток  €чейка как проходима€; ввод ложных меток ее как не проходимую
    public void setPassable(boolean pass)
    {
        passable = pass;
        updateAppearance();
    }
    
    // ¬озвращает true, если эта €чейка проходима, или false в противном случае
    public boolean isPassable()
    {
        return passable;
    }
    
    //ѕереключает текущее проходимое состо€ние €чейки карты
    public void togglePassable()
    {
        setPassable(!isPassable());
    }
    
    //ѕомечает эту €чейку как часть пути, обнаруженного алгоритмом A*
    public void setPath(boolean path)
    {
        this.path = path;
        updateAppearance();
    }
    
    //обновл€ет цвет фона в соответствии с текущим внутреннее состо€ние клетки  
    private void updateAppearance()
    {
        if (passable)
        {
            setBackground(Color.WHITE);

            if (endpoint)
                setBackground(Color.CYAN);
            else if (path)
                setBackground(Color.GREEN);
        }
        else
        { 
            setBackground(Color.RED);
        }
    }

    protected void paintComponent(Graphics g)
    {
        g.setColor(getBackground());
        g.fillRect(0, 0, getWidth(), getHeight());
    }
}
