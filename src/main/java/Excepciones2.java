
package Excepciones2;

import java.util.Scanner;

class NoExiste extends Exception {
    public NoExiste(String message) {
        super(message);
    }
}

class NoLugar extends Exception {
    public NoLugar(String message) {
        super(message);
    }
}

public class ExcepcionCine {
    public static int[] salas = { 50, 20, 20, 50, 20, 50, 150 };
    public static int opcion, sala, boletos;
    public static Scanner scan = new Scanner(System.in);

    public static void main(String[] args) throws NoLugar {

        while (true) {
            System.out.println("1.-Venta boletos\n2.-Cerrar taquilla");
            opcion = scan.nextInt();
            switch (opcion) {
                case 1:
                    System.out.println("En que sala?\nSalas\tLugares disponibles");
                    for (int i = 0; i < salas.length; i++) {
                        System.out.println((i + 1) + "\t\t" + salas[i] + "\n");
                    }
                    try {
                        sala = scan.nextInt() - 1;
                        //sala -= 1;
                        validaSala(sala);
                        System.out.println(salas[sala]);
                        System.out.println("Cuantos boletos desea?");
                        boletos = scan.nextInt();
                        Lugares(boletos);
                        salas[sala] -= boletos;
                    } catch (NoExiste e) {
                        System.out.println(e.getMessage());
                    } catch (NoLugar e) {
                        System.out.println(e.getMessage());
                    }
                    break;
                case 2:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Coloque una opcion correcta");
                    break;
            }
        }
    }

    private static void Lugares(int boletos) throws NoLugar {
        if (salas[sala] < 1) {
            throw new NoLugar("Ya no hay boletos");
        }
        if (boletos > salas[sala]) {
            throw new NoLugar("No hay suficientes lugares");
        }
    }

    private static void validaSala(int sala) throws NoExiste {
        if ((sala < 0) || (sala > 7)) {
            throw new NoExiste("No existe ese numero de salas");
        }

    }

}
