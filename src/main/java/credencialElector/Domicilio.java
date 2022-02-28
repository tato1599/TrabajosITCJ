/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package credencialElector;

/**
 *
 * @author esemi
 */
public class Domicilio {

    private String calle;
    private String colonia;
    private String municipio;
    private int codigoPostal;

    public Domicilio(String calle, String colonia, String municipio, int codigoPostal) {
        this.calle = calle;
        this.colonia = colonia;
        this.municipio = municipio;
        this.codigoPostal = codigoPostal;
    }

    public String getCalle() {
        return calle;
    }

    public void setCalle(String calle) {
        this.calle = calle;
    }

    public String getColonia() {
        return colonia;
    }

    public void setColonia(String colonia) {
        this.colonia = colonia;
    }

    public String getMunicipio() {
        return municipio;
    }

    public void setMunicipio(String municipio) {
        this.municipio = municipio;
    }

    public int getCodigoPostal() {
        return codigoPostal;
    }

    public void setCodigoPostal(int codigoPostal) {
        this.codigoPostal = codigoPostal;
    }

    @Override
    public String toString() {
        return "Domicilio{" + "calle=" + calle + ", colonia=" + colonia + ", municipio=" + municipio + ", codigoPostal=" + codigoPostal + '}';
    }

}
