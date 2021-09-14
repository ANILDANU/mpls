Commands to run the program(on linux):
$./routing -top top14.txt -conn NSFNET_100.txt -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag dist -p 0

$./routing -top top14.txt -conn NSFNET_100.txt -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag dist -p 1

$./routing -top top14.txt -conn NSFNET_100.txt -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag hop -p 0

$./routing -top top14.txt -conn NSFNET_100.txt -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag hop -p 1


$./routing -top top24.txt -conn ARPANET_100.txt -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag dist -p 0

$./routing -top top24.txt -conn ARPANET_100.txt -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag dist -p 1

$./routing -top top24.txt -conn ARPANET_100.txt -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag hop -p 0

$./routing -top top24.txt -conn ARPANET_100.txt -rt routingfile.txt -ft forwarding.txt -path pathfile.txt -flag hop -p 1


Note: *Please use .txt file instead of .doc file.
      For windows use routing.exe rest of the commands are same.

output Explaination:
routingfile.txt contains shortest path between two vertices two consecutive lines denotes the first and second shortest path.
forwarding.txt conatins forwading table entry for each router for each establsihed connection.
path.txt contains the total connections and total admitted connections.
connection.txt contains each admitted connection and their information with different fields.