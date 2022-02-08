import java.util.ArrayList;
import java.io.File;
import java.util.Scanner;

import java.util.*;

public class Hw03 {
    public static void main(String args[])  {
        ArrayList<String> input = new ArrayList<>();
		try {
			File myObj = new File(args[0]);   
			Scanner reader = new Scanner(myObj);
			 while (reader.hasNextLine()) {
			        String data = reader.nextLine();
			       input.add(data);
			      }
			 reader.close();
			
			} catch(Exception e) {
				e.printStackTrace();
            }
            

        int hashVal;
        for(int i = 0; i < input.size(); i++)
        {
            String str = input.get(i);
            hashVal = UCFxram(input.get(i), str.length());
        
            System.out.format("%10x:%s\n",hashVal, input.get(i));
            
        }
        System.out.println("Input file completed");

        complexityIndicator();
    }
        
            
public static int UCFxram(String input, int len) {

    
    int tempData = 0;
    byte [] d = input.getBytes();

    int randVal1 = 0xbcde98ef;
    int randVal2 = 0x7890face;

    int hashVal = 0xfa01bc96;
    int roundedEnd = len & 0xfffffffc; // Array d gets 4 byte blocks


        for (int i = 0; i < roundedEnd; i=i+4) {
            tempData = (d[i] & 0xff) | ((d[i+1] & 0xff) << 8) | ((d[i+2] & 0xff) << 16) | (d[i+3] << 24) ;
            tempData = tempData * randVal1; // Multiply
            tempData = Integer.rotateLeft(tempData, 12); // Rotate left 12 bits
            tempData = tempData * randVal2; // Another Multiply
            hashVal = hashVal ^ tempData;
            hashVal = Integer.rotateLeft(tempData, 13); // Rotate left 13 bits
            hashVal = hashVal * 5 + 0x46b645e;    
        }

        // Now collect orphan input characters
        tempData = 0;
        if ((len & 0x03) == 3) {
            tempData = (d[roundedEnd + 2] & 0xff) << 16;
            len = len - 1;
        }

        else if ((len & 0x03) == 2) {
            tempData |= (d[roundedEnd + 1] & 0xff) << 8;
            len = len - 1;
        }

        else if ((len & 0x03) == 1) {
            tempData |= (d[roundedEnd] & 0xff);
            tempData = tempData * randVal1; // Multiply
            tempdata = Integer.rotateLeft(tempData, 14);
            tempData = tempData * randVal2; // Another Multiply
            hashVal = hashVal ^ tempData;
        }
    hashVal = hashVal ^ len; // XOR
    hashVal = hashVal & 0xb6acbe58; // AND
    hashVal = hashVal ^ hashVal >>> 13;
    hashVal = hashVal * 0x53ea2b2c; // Another arbitary value
    hashVal = hashVal ^ hashVal >>> 16;

    return hashVal;
    }

    public static void complexityIndicator() {
        System.err.println("fr124772;2;2");
    }

}