/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package Paquetes;

import java.awt.Dialog;
import java.util.Scanner;
import javax.swing.JOptionPane;

/**
 *
 * @author esemi
 */
public class AppPaquetes {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        Scanner cap = new Scanner(System.in);
        int opcion, i=0;
        Caja Dia[] = new Caja[15];
      
        do {

            System.out.println("Menu");
            System.out.println("1.Crear caja");
            System.out.println("2.Imprimir");
            System.out.println("3.Salir");
            opcion = cap.nextInt();

            switch (opcion) {
                case 1:
                    System.out.println("Altas");
                    Dia[i] = altas();
                    i++;

                    break;
                case 2:
                    System.out.println("Ver Altas");
                    for (int x = 0; x < i; x++) {
                        System.out.println(Dia[x]);

                    }
                    break;
                case 3:
                    System.out.println("Salir");
                    break;
                default:
                    System.out.println("numero no valido");
                    break;
            }

        } while (opcion < 3);

    }

    public static Caja altas() {

        Scanner entrada = new Scanner(System.in);
        float largo, alto, ancho;
        System.out.println("Largo");
        largo = entrada.nextFloat();
        System.out.println("Alto");
        alto = entrada.nextFloat();
        System.out.println("Ancho");
        ancho = entrada.nextFloat();
        Caja cajita = new Caja(alto, largo, ancho);
        System.out.println(cajita);
        return cajita;
    }

}
