/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Paquetes;

/**
 *
 * @author esemi
 */
public class Caja {
    private float alto;
    private float ancho;
    private float largo;

    public Caja(float alto, float ancho, float largo) {
        this.alto = alto;
        this.ancho = ancho;
        this.largo = largo;
    }

    public float getAlto() {
        return alto;
    }

    public void setAlto(float alto) {
        this.alto = alto;
    }

    public float getAncho() {
        return ancho;
    }

    public void setAncho(float ancho) {
        this.ancho = ancho;
    }

    public float getLargo() {
        return largo;
    }

    public void setLargo(float largo) {
        this.largo = largo;
    }

    @Override
    public String toString() {
        return "Caja{" + "alto=" + alto + ", ancho=" + ancho + ", largo=" + largo + '}';
    }
    
    
    
}
