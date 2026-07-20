# Brazo Robótico

Proyecto de control de un brazo robótico industrial, con firmware para la placa de control y una aplicación de escritorio para el manejo y programación de movimientos.

## Estructura del repositorio

```
Brazo_robotico/
├── brazo_robotico_ardruino/   # Firmware / código embebido para el control del brazo
├── brazo_robotico_.net/       # Aplicación de escritorio (.NET / C#, Visual Studio)
│   └── Braccio Robotico.sln
└── README.md
```

- **`brazo_robotico_ardruino/`** — Código de control de bajo nivel para la placa (gestión de motores/servos, movimientos y comunicación con la aplicación de escritorio).
- **`brazo_robotico_.net/`** — Solución de Visual Studio (`Braccio Robotico.sln`) con la aplicación en C#/.NET que permite programar, ejecutar y supervisar los movimientos del brazo desde el PC.

## Requisitos

- [Visual Studio](https://visualstudio.microsoft.com/) (para compilar y ejecutar la parte `.net`)
- .NET SDK (versión según el proyecto)
- Arduino IDE o entorno equivalente (para compilar y subir el firmware)
- Placa de control compatible y componentes del brazo (servomotores, etc.)

## Puesta en marcha

1. Clona el repositorio:
   ```bash
   git clone https://github.com/antoniocorrea06/Brazo_robotico.git
   ```
2. Sube el firmware de `brazo_robotico_ardruino/` a la placa de control.
3. Abre `brazo_robotico_.net/Braccio Robotico.sln` en Visual Studio, compila y ejecuta la aplicación.
4. Conecta el PC con la placa y comienza a programar los movimientos del brazo.

## Autor

Antonio (Paco) Correa Rodríguez — [@antoniocorrea06](https://github.com/antoniocorrea06)

## Licencia

Sin licencia especificada por el momento.
