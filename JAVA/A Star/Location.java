/**
* Этот класс представляет определенное местоположение на 2D-карте. Координаты таковы
* целочисленные значения.
**/
public class Location
{
	//X координата этого местоположения
    public int xCoord;


    public int yCoord;


    //Создает новое местоположение с заданными целочисленными координатами
    public Location(int x, int y)
    {
        xCoord = x;
        yCoord = y;
    }

    // Создает новое местоположение с координатами (0, 0)  
    public Location()
    {
        this(0, 0);
    }

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + xCoord;
		result = prime * result + yCoord;
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Location other = (Location) obj;
		if (xCoord != other.xCoord)
			return false;
		if (yCoord != other.yCoord)
			return false;
		return true;
	}
    
    
}
