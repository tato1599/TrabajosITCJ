/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package credencialElector;

/**
 *
 * @author esemi
 */
public class Persona {

    private String nombre;
    private String fechaDeNacimiento;
    private char sexo;
    private int edad;

    public Persona(String nombre, String fechaDeNacimiento, char sexo, int edad) {
        this.nombre = nombre;
        this.fechaDeNacimiento = fechaDeNacimiento;
        this.sexo = sexo;
        this.edad = edad;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public String getFechaDeNacimiento() {
        return fechaDeNacimiento;
    }

    public void setFechaDeNacimiento(String fechaDeNacimiento) {
        this.fechaDeNacimiento = fechaDeNacimiento;
    }

    public char getSexo() {
        return sexo;
    }

    public void setSexo(char sexo) {
        this.sexo = sexo;
    }

    public int getEdad() {
        return edad;
    }

    public void setEdad(int edad) {
        this.edad = edad;
    }

    @Override
    public String toString() {
        return "Persona{" + "nombre=" + nombre + ", fechaDeNacimiento=" + fechaDeNacimiento + ", sexo=" + sexo + ", edad=" + edad + '}';
    }

}
