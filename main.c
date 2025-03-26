#include <stdio.h>
 
int main()
{
    int id = 0, stock = 0, cantidad = 0, opcion = 0;
    float precio = 0.0f, total_ganancias = 0.0f, venta = 0.0f;
    char nombre[30];
    int producto_registrado = 0;
 
    do
    {
        printf("\nMenu de Opciones:\n");
        printf("1. Registrar Producto\n");
        printf("2. Vender producto\n");
        printf("3. Reabastecer producto\n");
        printf("4. Mostrar informacion del producto\n");
        printf("5. Mostrar total de ganancias\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
 
        if (producto_registrado <= 0 && opcion != 1)
        {
            printf("Primero debe registrar los datos del producto.\n");
            printf("Seleecione 1 para poder hacerlo");
            continue;  
        }
 
        switch (opcion)
        {
        case 1:
            do
            {
                printf("Ingrese el ID del producto: \n");
                scanf("%d", &id);
                if (id < 0)
                {
                    printf("El id no puede ser negativo\n");
                }
            } while (id < 0);
 
            printf("Ingrese el nombre del producto: \n ");
            fflush(stdin);
            fgets(nombre, 30, stdin);
            do
            {
                printf("Ingrese la cantidad inicial en stock: \n ");
                scanf("%d", &stock);
                if (stock <= 0)
                {
                    printf("El stock no puede ser menor que 0\n");
                }
            } while (stock <= 0);
 
            do
            {
                printf("Ingrese el precio unitario del producto: \n ");
                scanf("%f", &precio);
 
                if (precio < 0)
                {
                    printf("El precio unitario no puede ser menor que 0\n");
                }
            } while (precio <= 0);
            producto_registrado = 1;
            printf("ID: %d\n", id);
            printf("Nombre: %s", nombre);
            printf("Stock disponible: %d\n", stock);
            printf("Precio unitario: %.2f\n", precio);
            break;
 
        case 2:
            do
            {
                printf("Ingrese la cantidad a vender: ");
                scanf("%d", &cantidad);
                if (cantidad < 1)
                {
                    printf("La cantidad debe ser mayor a cero, vuelva a ingresar la cantidad;\n");
                }
                if (cantidad > stock)
                {
                    printf("No existe el stock suficiente para esta venta, ingrese una cantidad");
                }
            } while (cantidad < 1 || cantidad > stock);
 
            venta = cantidad * precio;
            total_ganancias+= venta;
            stock-= cantidad;
            printf("El total de la venta es: %.2f\n", venta);
            break;
 
        case 3:
            printf("Ingrese la cantidad a agregar al stock: ");
            scanf("%d", &cantidad);
            if (cantidad>0)
            {
                stock += cantidad;
                printf("El stock actualizado es: %d\n",stock);
            }
            else
            {
                printf("La cantidad debe ser mayor que 0\n");
            }
            break;
 
        case 4:
            printf("\nInformacion del producto:\n");
            printf("ID: %d\n", id);
            printf("Nombre: %s", nombre);
            printf("Stock disponible: %d\n", stock);
            printf("Precio unitario: %.2f\n", precio);
            break;
 
        case 5:
            printf("Total de ganancias: $%.2f\n", total_ganancias);
            break;
 
        case 6:
            printf("Saliendo del programa...\n");
            break;
 
        default:
            printf("Opción invalida. Intente nuevamente.\n");
        }
    } while (opcion != 6);
 
    return 0;
}