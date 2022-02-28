package credencialElector;

public class AppCredencial {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        //public Domicilio(String calle, String colonia, String municipio, int codigoPostal)
        Persona persona1 = new Persona("Daniel Octavio Ramirez Neri", "15 de octubre de 1999", 'H', 22);
        System.out.println(persona1);
        Domicilio domicilio1 = new Domicilio("Año 1872", "Colonia Benito Juarez", "Juarez", 32390);
        System.out.println(domicilio1);
        //public Credencial(Persona personaEnCredencial, Domicilio domicilioPersona, String cita, String curpPersona)
        Credencial credencial1 = new Credencial(persona1,domicilio1,"10:00 a.m","RAND991015HCHMRN00");
        System.out.println(credencial1);
    }

}
