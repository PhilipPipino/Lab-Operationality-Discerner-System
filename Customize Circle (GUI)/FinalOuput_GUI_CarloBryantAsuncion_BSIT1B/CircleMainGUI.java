package FinalOuput_GUI_CarloBryantAsuncion_BSIT1B;
import java.awt.*;
import javax.swing.*;

//Main class of "FinalOutput" package
public class CircleMainGUI {
    public static void main(String[] args) {
    	
    	//JFrame instantiation
        JFrame frm=new JFrame("Circle Customizer");
        
        //Circle instantiation
        Circle circle=new Circle(Color.RED,"",315,123,150);
        
        //JPanel instantiation for the button panel
        JPanel mainPnl=new JPanel();
    	
        	//Instantiation of  upper button panel
    		JPanel topPnl=new JPanel();
    		
    			//Text area and set button for circle name
    			JTextField textbox=new JTextField(20);
    			JButton setNameButton=new JButton("Enter Circle Name");
    				//Implements the actionPerformed method in separate class with lambda
    				setNameButton.addActionListener(e->{
    					String name=textbox.getText();
    					circle.setName(name);
    					System.out.println("SET NAME BUTTON CLICKED, "
    									+ "circle is now named: "+name);
    				});
    				
    		//Adds the text field and the set name button
    		topPnl.add(textbox);
    		topPnl.add(setNameButton);
        
    		//Instantiation of bottom button panel
    		//where the three buttons will be located
    		JPanel bottomPnl=new JPanel();
    		
    		//Instantiates concrete buttons from abstract class
    		Button b1=new PositionButton("Center Circle",circle);
    		Button b2=new ColorButton("Change Color",circle);
    		Button b3=new SizeButton("Change Size",circle);
    			
    			//Concrete buttons added to bottom panel
    			bottomPnl.add(b1);
    			bottomPnl.add(b2);
    			bottomPnl.add(b3);
    		
    		//Top and the bottom button panels are
    		//added to the main one, with a layout
    		//of two rows and one column
    		mainPnl.setLayout(new GridLayout(2,1));
    		mainPnl.add(topPnl);
    		mainPnl.add(bottomPnl);
        
    	//Adds and sets all necessary components
    	//to the JFrame object
        frm.add(circle, BorderLayout.CENTER);
        frm.add(mainPnl, BorderLayout.SOUTH);
        frm.setSize(800, 500);
        frm.setResizable(false);
        frm.setVisible(true);
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}