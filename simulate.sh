g++ transmitter.cpp -o transmitter
g++ reciver.cpp -o reciver -l curl
g++ gen.cpp -o gen
g++ togendata.cpp -o togendata 

TIMEFORMAT=%R
./gen<startvar>gendata
for(( i=0;;i++))
do
    sleep 1
    echo "$i"
	./transmitter<gendata>out.out;
    ./reciver>rec
    #  cat gendata

    cat rec
    echo " "
    ./gen<gendata>help
    ./togendata<help>gendata
done