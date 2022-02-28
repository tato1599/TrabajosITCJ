/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package credencialElector;

/**
 *
 * @author esemi
 */
public class Credencial {

    private Persona personaEnCredencial;
    private Domicilio domicilioPersona;
    private String cita;
    private String curpPersona;

    public Credencial(Persona personaEnCredencial, Domicilio domicilioPersona, String cita, String curpPersona) {
        this.personaEnCredencial = personaEnCredencial;
        this.domicilioPersona = domicilioPersona;
        this.cita = cita;
        this.curpPersona = curpPersona;
    }

    @Override
    public String toString() {
        return "Credencial{" + "personaEnCredencial=" + personaEnCredencial + ", \n domicilioPersona=" + domicilioPersona + ",\n cita=" + cita + ",\n curpPersona=" + curpPersona + '}';
    }

}
