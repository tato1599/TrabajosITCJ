/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package conver;

import java.util.Stack;

/**
 *
 * @author esemi
 */
public class Convertir {

    private String expresion;

    public Convertir(String expresion) {
        this.expresion = expresion;
    }

    public String InPos() {
        Stack pila = new Stack();
        String aux = "";
        String s = this.expresion;
        for (int i = 0; i < s.length(); i++) {
            if (Character.isLetterOrDigit(s.charAt(i))) {
                aux += s.charAt(i);
            } else {

                if (s.charAt(i) == ')') {

                    while (!pila.empty()) {
                        if (pila.peek().equals(')') || pila.peek().equals('(')) {
                            pila.pop();
                        } else {
                            aux += pila.peek();
                            pila.pop();
                        }
                    }

                }
                if (!pila.empty()) {
                    if (((s.charAt(i) == '+' || s.charAt(i) == '-') && (pila.peek().equals('*') || pila.peek().equals('/'))) || (s.charAt(i) == '/' && pila.peek().equals('*'))) {

                        if (!pila.peek().equals(')')) {
                            aux += pila.peek();
                            pila.pop();
                        } else {
                            pila.pop();
                        }

                    }
                }
                pila.push(s.charAt(i));
            }

        }

        while (!pila.empty()) {
            if (!pila.peek().equals(')')) {
                aux += pila.peek();
                pila.pop();
            } else {
                pila.pop();
            }

        }

        return aux;
       // System.out.println(pila);
    }

    // + y - mismo orden de presedencia 
    // / y * mayor que suma y resta
    // ^ mayor que division y multiplicacion
}
