package FinalOuput_GUI_CarloBryantAsuncion_BSIT1B;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import javax.swing.JPanel;

//Circle inherits JPanel java class 
//and uses MouseListener and MouseMotionListener interface
public class Circle extends JPanel implements MouseListener, MouseMotionListener {
	
	//Auto-generated UID, required in compilation
	private static final long serialVersionUID = 1454677079891416830L;
	
	//Encapsulated variables
    private String name;
    private int x, y, size, distx, disty;
    //Encapsulated color object declaration
    private Color color;
    
    //Drag area rectangular space instantiation
    private Rectangle space=new Rectangle(15,30,750,335);
    
    //Circle constructor method to create circle object
    public Circle(Color color,String name,int x,int y,int size) {
        this.color=color;
        this.name=name;
        this.x=x;
        this.y=y;
        this.size=size;
        
        addMouseListener(this);
        addMouseMotionListener(this);
    }
    //Graphics paint method declaration
    public void paintComponent(Graphics g) {
    	
    	//Clears components and paints the space
        super.paintComponent(g);
        //Instantiates the object "g2d"
        Graphics2D g2d=(Graphics2D) g;
        
        //Paints rectangle drag area
        g2d.setColor(Color.LIGHT_GRAY);
        g2d.fillRect(space.x, space.y, space.width, space.height);
        
        //Paints the circle
        g2d.setColor(color);
        g2d.fillOval(x, y, size, size);
        
        //Paints the circle name,
        //centered above the circle
        g2d.drawString(name, x+size/2-g2d.getFontMetrics().stringWidth(name)/2, y-10);
    }
    @Override
    public void mouseClicked(MouseEvent e) {}
    @Override
    public void mousePressed(MouseEvent e) {
    	//When user clicks within the circle, 
    	//x & y distance from the edge is taken
    	if(e.getX()>=x && e.getX()<=x+size
		&& e.getY()>=y && e.getY()<=y+size){
				distx=e.getX()-x; 
				disty=e.getY()-y;
				}
    }
    @Override
    public void mouseReleased(MouseEvent e) {}
    @Override
    public void mouseEntered(MouseEvent e) {}
    @Override
    public void mouseExited(MouseEvent e) {}
    @Override
    public void mouseDragged(MouseEvent e) {
    		//Drags circle while maintaining distance
			if(e.getX()>=x && e.getX()<=x+size
			&& e.getY()>=y && e.getY()<=y+size){
				x=e.getX()-distx; 
				y=e.getY()-disty; 
					
				//Limits circle within the gray space
				if(x<=space.x) x=space.x;
				if(x+size>=space.x+space.width) x=space.x+space.width-size;
				if(y<=space.y) y=space.y;
				if(y+size>=space.y+space.height) y=space.y+space.height-size;
				repaint();
				}
    }
    @Override
    public void mouseMoved(MouseEvent e) {}
    
    //color object setter
    public void setColor(Color color) {
        this.color=color;
    }
    //Center circle position method
    public void centerPosition() {
    	//Positions the circle in the center of the space
        x=space.x+space.width/2-size/2;
        y=space.y+space.height/2-size/2;
        repaint();
    }
    //circle integer size setter
    public void setCircleSize(int size) {
        this.size=size;
    }
    //circle integer size getter
    public int getCircleSize() {
        return size;
    }
    //current circle x & y position setter
    public void setCirclePos(int x, int y) {
        this.x=x;
        this.y=y;
    }
    //circle x position getter
    public int getCircleXPos() {
        return x;
    }
    //circle y position getter
    public int getCircleYPos() {
        return y;
    }
    //circle name setter
    public void setName(String name) {
        this.name=name;
        repaint();
    }
}