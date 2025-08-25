import java.util.HashMap;
/**
Этот класс хранит базовое состояние, необходимое алгоритму A* для вычисления
пути по карте. Это состояние включает в себя коллекцию "открытых путевых точек" и
другую коллекцию "закрытых путевых точек".
Кроме того, этот класс предоставляет
основные операции, необходимые алгоритму поиска пути A* для выполнения его обработки.
 **/
public class AStarState
{
    //ссылка на карту, по которой перемещается алгоритм A*.
    private Map2D map;
    
   private  HashMap<Location, Waypoint> openWaypoint = new HashMap<>();
   private  HashMap<Location, Waypoint> closeWaypoint = new HashMap<>();

    // Инициализация нового объекта состояния для использования алгоритма поиска пути
    public AStarState(Map2D map)
    {
        if (map == null)
            throw new NullPointerException("map cannot be null");

        this.map = map;
    }

    //Возвращает карту по которой перемещается навигатор A*
    public Map2D getMap()
    {
        return map;
    }
    
    
    //Возвращает текущее количество открытых путевых точек
    public int numOpenWaypoints()
    {
        return openWaypoint.size();
    }
    
    //сканирует все открытые путевые точки и возвращает путевую точку с минимальными общими затратами. 
    //Если открытых путевых точек нет, этот метод возвращает <code>null</code>
    public Waypoint getMinOpenWaypoint()
    {
		if(openWaypoint.size()==0) return null;
		
		  Waypoint min;
		  Waypoint massWaypoin[] = new Waypoint[numOpenWaypoints()]; 
		  int i = 0;
			  
		  for(Waypoint a : openWaypoint.values()) 
		  { 
			  massWaypoin[i]=a; 
			  i++; 
		  }
		  
		  min=massWaypoin[0];
		  
		  for(i=1; i<numOpenWaypoints(); i++) 
		  {
			  if(massWaypoin[i].getTotalCost()<min.getTotalCost()) 
			  { 
				  min = massWaypoin[i];
			  } 
		  }
			
		  return min;

    }

    /*
      Этот метод добавляет путевую точку к уже существующей (или потенциально обновляет ее
      в) коллекция "открытые путевые точки".  Если еще нет открытого
      путевая точка в местоположении новой путевой точки, то новая путевая точка просто
      добавлено в коллекцию.  Однако если вместоположении 
      new waypoint уже есть путевая точка, то новая путевая точка заменяет только старую <em>.
      если</em> значение "предыдущей стоимости" новой путевой точки меньше текущей
      значение "предыдущей стоимости" путевой точки.     **/
    public boolean addOpenWaypoint(Waypoint newWP)
    {
    	Waypoint a = openWaypoint.get(newWP.getLocation());
        if (a == null || newWP.getPreviousCost() < a.getPreviousCost())
        {
            openWaypoint.put(newWP.getLocation(), newWP);
            return true;
        }
        return false;
    }
    // Возвращает true, если коллекция закрытых путевых точек содержит путевую точку для указанного местоположения. 
        public boolean isLocationClosed(Location loc)
        {
        	if(closeWaypoint.containsKey(loc)) return true;
            return false;
        }
    
    //еремещает путевую точку в указанном месте из открытого списка в закрытый
     **/
    public void closeWaypoint(Location loc)
    {
    	closeWaypoint.put(loc,openWaypoint.get(loc));
    	openWaypoint.remove(loc);	
    }

 
}

