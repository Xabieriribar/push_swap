#!/bin/bash

# ---------------- CONFIGURACIÓN ----------------
# Cantidad de números a probar (puedes cambiarlo al ejecutar: ./test_leaks.sh 100)
CANTIDAD=${1:-100}
PROG="./push_swap"

# Colores para la salida
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# ---------------- COMPILACIÓN ----------------
echo -e "${YELLOW}>>> Compilando push_swap...${NC}"
make re > /dev/null
if [ ! -f "$PROG" ]; then
    echo -e "${RED}Error: No se encuentra el ejecutable $PROG${NC}"
    exit 1
fi
echo -e "${GREEN}>>> Compilación exitosa.${NC}"

# ---------------- GENERADOR DE ARGUMENTOS ----------------
# Genera una secuencia de números aleatorios sin duplicados (usando Ruby por compatibilidad)
ARG=$(ruby -e "puts (1..$CANTIDAD).to_a.shuffle.join(' ')")

# ---------------- EJECUCIÓN DEL TEST ----------------
echo -e "${YELLOW}>>> Probando con $CANTIDAD números aleatorios...${NC}"

# Detectar sistema operativo para elegir la herramienta
OS=$(uname)

if [ "$OS" = "Linux" ]; then
    # Comprobación con VALGRIND (Estándar en 42/Linux)
    if command -v valgrind &> /dev/null; then
        OUTPUT=$(valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $PROG $ARG 2>&1)
        
        if echo "$OUTPUT" | grep -q "ERROR SUMMARY: 0 errors"; then
            echo -e "${GREEN}[OK] No se detectaron Memory Leaks.${NC}"
        else
            echo -e "${RED}[KO] Se detectaron LEAKS o ERRORES:${NC}"
            echo "$OUTPUT" | grep -A 5 "LEAK SUMMARY"
            echo "$OUTPUT" | grep "ERROR SUMMARY"
        fi
    else
        echo -e "${RED}Error: Valgrind no está instalado.${NC}"
    fi

elif [ "$OS" = "Darwin" ]; then
    # Comprobación con LEAKS (macOS)
    # Nota: 'leaks' requiere que el programa esté corriendo, por lo que ejecutamos y revisamos el exit code o usamos 'leaks -atExit'
    
    echo -e "${YELLOW}Nota: En macOS asegúrate de no usar fsanitize al compilar para este test.${NC}"
    $PROG $ARG > /dev/null & PID=$!
    leaks $PID > leaks_output.txt
    wait $PID
    
    if grep -q "0 leaks for 0 total leaked bytes" leaks_output.txt; then
        echo -e "${GREEN}[OK] No se detectaron Memory Leaks.${NC}"
    else
        echo -e "${RED}[KO] Se detectaron LEAKS:${NC}"
        grep "leaks for" leaks_output.txt
    fi
    rm leaks_output.txt
fi

echo -e "${YELLOW}>>> Fin del test.${NC}"