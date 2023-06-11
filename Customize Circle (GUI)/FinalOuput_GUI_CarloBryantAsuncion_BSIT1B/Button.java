package FinalOuput_GUI_CarloBryantAsuncion_BSIT1B;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;

//Abstract "Button" class
public abstract class Button extends JButton implements ActionListener {
 
	//Auto-generated UID, required in compilation
	private static final long serialVersionUID = -2450038938475083218L;
	
	//Button constructor method to create objects of button
	public Button(String text) {
		//JButton text
        super(text);
        addActionListener(this);
    }
	
	//Event method declaration
    public void actionPerformed(ActionEvent e) {
    	System.out.println("Override this method");
	}
    
    private int clicks=1;
    	//clicks getter
    	public int getClicks(){
    		return clicks;
    	}
    	//clicks setter
    	public void setClicks(int clicks){
    		this.clicks=clicks;
    	}
}
