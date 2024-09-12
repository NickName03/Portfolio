# очистка экрана
echo -e "\E[H\E[2J"

# верхняя линия
echo -ne "\E[5;10H" #goto
echo -ne "\E(0l\E(B" #topleft bord
for ((i=1;i<9;i++)) do
echo -ne "\E(0q\E(B" #horizontal line
done
echo -e "\E(0k\E(B" #topright bord

# линии по бокам
echo -ne "\E[6;10H" #goto
for ((i=1;i<9;i++)) do
echo -e "\E[$((5+$i));10H\E(0x        x\E(B" #vertical line
done

# нижняя линия
echo -ne "\E[13;10H" #goto
echo -ne "\E(0m\E(B" #bottomleft bord
for ((i=1;i<9;i++)) do
echo -ne "\E(0q\E(B" #horizontal line
done
echo -e "\E(0j\E(B" #bottomright bord

#большая цифра
for ((i=0; i<7;i++)) do
echo -ne "\E[6;$((11+$i))H\E(0x" #goto
echo -ne "\E(0a\E(B" #ACS_CKBOARD (закрашенный прямоугольник)
done
for ((i=0; i<6;i++)) do
echo -ne "\E[$((7+$i));$((16-$i))H\E(0x" #goto
echo -ne "\E(0a\E(B"
done

echo -ne "\E[15;0H" #goto