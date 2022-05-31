/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Excepciones;

import java.util.Scanner;

/**
 *
 * @author 701
 */
class NoExiste extends Exception{
    public NoExiste(String message){
        super(message);
    }
}

class NoLugar extends Exception{
    public NoLugar(String message){
        super(message);
    }
}

public class ExcepcionCine {
    public static void main(String[] args) throws NoLugar {
        int[] salas = {50,20,20,50,20,50,150};
        Scanner scan = new Scanner(System.in);
        int opcion,sala,boletos;
        while(true){
            System.out.println("1.-Venta boletos\n2.-Cerrar taquilla");
            opcion = scan.nextInt();
            switch (opcion) {
            //En proceso xd
                case 1:
                    System.out.println("En que sala?");
                  
                    try{
                        sala = scan.nextInt();
                        validaSala(sala);
                    }
                    catch (NoExiste e) {
                        
                    }
                    
                    
                    break;
            //System.exit(0);
                case 2:
                    break;
                default:
                    break;
            }
        }
    }

    private static void validaSala(int sala) throws NoExiste , NoLugar {
        if((sala<1)||(sala>7)){
            throw new NoExiste("No existe ese numero de salas");
        }
    }
    
}
