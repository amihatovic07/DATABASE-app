#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;
#include <algorithm>

string malim(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}
struct podatak{
	string ime;
	float cijena;
	int godine;
	float kvaliteta;
};
void izbornik(){
	cout<<"------------------\n";
	cout<<"||1. Sortiranje   ||\n";
	cout<<"------------------\n";
	cout<<"||2. Dodavanje    ||\n";
	cout<<"------------------\n";
	cout<<"||3. Micanje      ||\n";
	cout<<"------------------\n";
	cout<<"||4. Pretrazivanje||\n";
	cout<<"------------------\n";
	cout<<"||5. Pohrana      ||\n";
	cout<<"------------------\n";
	cout<<"||6. Izlaz        ||\n";
	cout<<"------------------\n";
}
void izbornik1(){
	cout<<"------------------\n";
	cout<<"||1. Cijenama    ||\n";
	cout<<"------------------\n";
	cout<<"||2. Godinama    ||\n";
	cout<<"------------------\n";
	cout<<"||3. Kvaliteti   ||\n";
	cout<<"------------------\n";
	cout<<"||4. natrag      ||\n";
	cout<<"------------------\n";
}
void izbornik2(){
	cout<<"------------------\n";
	cout<<"||1. Imenu       ||\n";
	cout<<"------------------\n";
	cout<<"||2. Cijenama    ||\n";
	cout<<"------------------\n";
	cout<<"||3. Godinama    ||\n";
	cout<<"------------------\n";
	cout<<"||4. Kvaliteti   ||\n";
	cout<<"------------------\n";
	cout<<"||5. natrag      ||\n";
	cout<<"------------------\n";
}
void spremiuBAZU(const podatak podatci[], int count, const string& filename){
	ofstream out(filename.c_str());
	if(!out){
		cout<<"Greska: ne mogu otvoriti datoteku za pisanje!\n";
		return;
	}
	out<<"ime;cijena;godine;kvaliteta\n";
	for (int i=0;i<count;i++){
		out<<podatci[i].ime<<";"<<podatci[i].cijena<<";"<<podatci[i].godine<<";"<<podatci[i].kvaliteta<<"\n";
	}
	cout<<"Pohranjeno u datoteku: "<<filename<<"\n";
}
void sortiraj(podatak podatci[], int count, string polje, bool uzlazno) {
	for (int i = count-1; i > 0; i--) {
		for( int j = 0; j < i; j++) {
			bool zamijeni = false;
			if (polje=="cijena") {
				zamijeni = uzlazno ? podatci[j].cijena > podatci[j+1].cijena : podatci[j].cijena < podatci[j+1].cijena;
			}
			else if (polje=="godine") {
				zamijeni = uzlazno ? podatci[j].godine > podatci[j+1].godine : podatci[j].godine < podatci[j+1].godine;
			}
			else if (polje=="kvaliteta") {
				zamijeni = uzlazno ? podatci[j].kvaliteta > podatci[j+1].kvaliteta : podatci[j].kvaliteta < podatci[j+1].kvaliteta;
			}
			if (zamijeni) {
				podatak pom=podatci[j];
				podatci[j]=podatci[j+1];
				podatci[j+1]=pom;
			}
		}
	}
}
int ucitajIzBaze(podatak podatci[], const string& filename) {
	ifstream in(filename.c_str());
	if (!in) return 0;
	int count=0;
	string linija;
	getline(in,linija);
	while(getline(in, linija)) {
		stringstream ss(linija);
		string dio;
		getline(ss, podatci[count].ime, ';');
		getline(ss, dio, ';'); podatci[count].cijena = stof(dio);
		getline(ss, dio, ';'); podatci[count].godine = stof(dio);
		getline(ss, dio, ';'); podatci[count].kvaliteta = stof(dio);
		count++;
	}
	return count;
}
int main() {
	podatak podatci[100];
	string odg, pod, pod1, odabir1, odabir2, odabir3;
	int n, m, y, pod2;
	float pod3;
	
	int count = ucitajIzBaze(podatci, "baza.txt");
	cout<<"***DOBRODOSLI***\n";
	cout<<"----------------\n";
	cout<<"Ovo je program unosa, analize, pohrane i rada sa podatcima opcenitog tipa.\n bitno samo da se definira o kakvom tipu podataka se radi!\n";
	do{
		cout<<"Zelite li koristiti ovaj program?: ";
		cin>>odg;
		if (malim(odg)=="da"){
			cout<<"u redu idemo dalje onda!\n";
			break;
		}
		else if (malim(odg)=="ne"){
			return 0;
		}
		else{
			continue;
		}
	} while (true);
	cout<<"u redu, sa cime se zelite baviti, kakav tocno oblik podataka zelite obradivati npr.(auti, brodovi, kuce...)?: ";
	cin>>pod;
	cout<<"u redu, dakle baviti cemo se s podatcima o "<<pod<<", zanimljivo!\n";
	cout<<"pa da pocnemo!\n";
	do{
		cout<<"za koliko cemo podataka unijeti informacije od "<<pod<<"?: ";
		cin>>n;
	} while (n<1||n>100);
	for (int i=0;i<n;i++){
		cout<<count+i+1<<". informacija za podatke koje trazite\n";
		cout<<"unesite ime od ove jedinice: ";
		cin.ignore();
		getline(cin, podatci[count+i].ime);
		do{
			cout<<"unesite cijenu od ove jedinice: ";
			cin>>podatci[count+i].cijena;
		} while (podatci[count+i].cijena<0||podatci[count+i].cijena>1000000000000);
		do{
			cout<<"unesite koje godine je proizvedena ova jedinica: ";
			cin>>podatci[count+i].godine;
		} while (podatci[count+i].godine<1||podatci[count+i].godine>2026);
		do{
			cout<<"unesite omjer kvalitete ove jedinice od 0.1 do 10: ";
			cin>>podatci[count+i].kvaliteta;
		} while (podatci[count+i].kvaliteta<0.1||podatci[count+i].kvaliteta>10);
	}
	count += n;
	cout<<"sada imamo unesene sve informacije za trazene podatke, sada ih obradujemo!\n";
	izbornik();
	cout<<"vas izbor: ";
	cin>>odabir1;
	do{
		if (malim(odabir1)=="1"||malim(odabir1)=="sortiranje"){
			do{	
				cout<<"Po kojem uvjetu zelite sortirati?";
				izbornik1();
				cout<<"vas izbor: ";
				cin>>odabir2;
				if (malim(odabir2)=="1"||malim(odabir2)=="cijena"){
					do{
						cout<<"zelite li uzlazno ili silazno sortiranje?: ";
						cin>>odabir3;
						if (malim(odabir3)=="silazno"){
							sortiraj(podatci, count, "cijena", false);
							for (int i=0;i<count;i++){
								cout<<"| "<<podatci[i].ime<<" | "<<podatci[i].cijena<<" | "<<podatci[i].godine<<" | "<<podatci[i].kvaliteta<<" |\n|-------------------------------------------------------------------------|\n";
							}
						}
						else if (malim(odabir3)=="uzlazno"){
							sortiraj(podatci, count, "cijena", true);
							for (int i=0;i<count;i++){
								cout<<"| "<<podatci[i].ime<<" | "<<podatci[i].cijena<<" | "<<podatci[i].godine<<" | "<<podatci[i].kvaliteta<<" |\n|-------------------------------------------------------------------------|\n";
							}
						}
						else if (malim(odabir3)=="natrag"){
							break;
						}
						else{
							cout<<"pogresan unos, pokusajte ponovo!\n";
							continue;
						}
					} while (true);
				}
				else if (malim(odabir2)=="2"||malim(odabir2)=="godina"){
					do{
						cout<<"zelite li uzlazno ili silazno sortiranje?: ";
						cin>>odabir3;
						if (malim(odabir3)=="silazno") {
							sortiraj(podatci, count, "godine", false);
							for (int i=0;i<count;i++){
								cout<<"| "<<podatci[i].ime<<" | "<<podatci[i].cijena<<" | "<<podatci[i].godine<<" | "<<podatci[i].kvaliteta<<" |\n|-------------------------------------------------------------------------|\n";
							}
						}
						else if	(malim(odabir3)=="uzlazno") {
							sortiraj(podatci, count, "godine", true);
							for (int i=0;i<count;i++){
								cout<<"| "<<podatci[i].ime<<" | "<<podatci[i].cijena<<" | "<<podatci[i].godine<<" | "<<podatci[i].kvaliteta<<" |\n|-------------------------------------------------------------------------|\n";
							}
						}
						else if (malim(odabir3)=="natrag"){
							break;
						}
						else{
							cout<<"pogresan unos, pokusajte ponovo!\n";
							continue;
						}
					} while(true);
				}
				else if (malim(odabir2)=="3"||malim(odabir2)=="kvaliteta"){
					do{
						cout<<"zelite li uzlazno ili silazno sortiranje?: ";
						cin>>odabir3;
						if (malim(odabir3)=="silazno") {
							sortiraj(podatci, count, "kvaliteta", false);
							for (int i=0;i<count;i++){
								cout<<"| "<<podatci[i].ime<<" | "<<podatci[i].cijena<<" | "<<podatci[i].godine<<" | "<<podatci[i].kvaliteta<<" |\n|-------------------------------------------------------------------------|\n";
							}
						}
						else if (malim(odabir3)=="uzlazno") {
							sortiraj(podatci, count, "kvaliteta", true);
							for (int i=0;i<count;i++){
								cout<<"| "<<podatci[i].ime<<" | "<<podatci[i].cijena<<" | "<<podatci[i].godine<<" | "<<podatci[i].kvaliteta<<" |\n|-------------------------------------------------------------------------|\n";
							}
						}
						else if (malim(odabir3)=="natrag"){
							break;
						}
						else{
							cout<<"pogresan unos, pokusajte ponovo!\n";
							continue;
						}
					} while (true); 
				}
				else if (malim(odabir2)=="natrag"){
					break;
				}
				else{
					cout<<"pogresan unos, pokusajte ponovo!\n";
					continue;
				}
			} while (true);
		}
		else if (malim(odabir1)=="2"||malim(odabir1)=="dodaj") {
			do{
				cout<<"zelite li dodati jos podataka?: ";
				cin>>odabir2;
				if (malim(odabir2)=="da"){
					do{
						cout<<"koliko zelite dodati novih podataka?: ";
						cin>>m;
						if (count+m>100) m=100-count;
						cin.ignore(numeric_limits<streamsize>::max(),'\n');
						for (int i=0;i<m;i++){
							int idx=count+i;
							cout<<(idx+1)<<". novi podatak\n";
							cout<<"unesite ime od ove jedinice: ";
							getline(cin, podatci[idx].ime);
							do{
								cout<<"unesite cijenu od ove jedinice: ";
								cin>>podatci[idx].cijena;
							} while (podatci[idx].cijena<0||podatci[idx].cijena>1000000000000);
							do{
								cout<<"unesite koje godine je proizvedena ova jedinica: ";
								cin>>podatci[idx].godine;
							} while (podatci[idx].godine<1||podatci[idx].godine>2026);
							do{
								cout<<"unesite omjer kvalitete ove jedinice od 0.1 do 10: ";
								cin>>podatci[idx].kvaliteta;
							} while (podatci[idx].kvaliteta<0.1||podatci[idx].kvaliteta>10);
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
						count +=m;
						for (int i=0;i<count;i++){
							cout<<"| "<<podatci[i].ime<<" | "<<podatci[i].cijena<<" | "<<podatci[i].godine<<" | "<<podatci[i].kvaliteta<<" |\n|-------------------------------------------------------------------------|\n";
						}
						break;
					} while (true);
				}
				else if (malim(odabir2)=="ne"){
					cout<<"u redu, onda idemo natrag!\n";
					break;
				}
				else{
					cout<<"pogresan unos, pokusajte ponovo!\n";
					continue;
				}
			} while (true);
		}
		else if (malim(odabir1)=="3"||malim(odabir1)=="makni") {
			do{
				cout<<"zelite li maknuti nesto?: ";
				cin>>odabir2;
				if (malim(odabir2)=="da"){
					cout<<"u redu, pocnimo onda!\n";
					string brisi;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout<<"sto zelite maknuti?: ";
					cin>>brisi;
					bool found=false;
					for (int i=0;i<count;i++){
						if (podatci[i].ime==brisi){
							for (int j=i;j<count-1;j++){
								podatci[j]=podatci[j+1];
							}
							count--;
							found=true;
							cout<<"obrisano!\n";
							break;
						}
					}
					if (!found) cout<<"Nije pronadeno!\n";
				}
				else if(malim(odabir2)=="ne"){
					cout<<"u redu, idemo natrag!\n";
					break;
				}
				else{
					cout<<"pogresan unos, pokusajte ponovo!\n";
					continue;
				}
			} while (true);
		}
		else if (malim(odabir1)=="4"||malim(odabir1)=="pretrazi") {
			do{
				cout<<"odaberite po kojem uvjetu zelite pretraziti podatke.\n";
				izbornik2();
				cout<<"unesite vas odabir: ";
				cin>>odabir2;
				if (malim(odabir2)=="1"||malim(odabir2)=="ime"){
					do{
						cout<<"unesite kako se zove to sto trazite, ukoliko se zelite vratiti upisite natrag: ";
						cin>>pod1;
						bool found=false;
						int index=-1;
						for(int i=0;i<count;i++){
							if (podatci[i].ime==pod1){
								found=true;
								index=i;
							}	
						}
						if (found){
							cout<<podatci[index].ime<<" se nalazi na "<<index+1<<". mjestu i cijelukupni podatci koje obuhvaca su: \n"<<"|-------------------------------------------------------------------------|\n| "<<podatci[index].ime<<" | "<<podatci[index].cijena<<" | "<<podatci[index].godine<<" | "<<podatci[index].kvaliteta<<" |\n|-------------------------------------------------------------------------|\n";
						}
						else if(!found) cout<<"nazalost to se ne nalazi u bazi podataka!\n";
						if (malim(pod1)=="natrag"){
							cout<<"idemo natrag!\n";
							break;
						}
						else{
							cout<<"pogresan unos, pokusajte ponovo!\n";
							continue;
						}
					} while (true);
				}
				else if (malim(odabir2)=="2"||malim(odabir2)=="cijena"){
					do{
						cout<<"unesite koja je cijena koju trazite od podataka, ukoliko se zelite vratiti upisite natrag: ";
						cin>>pod3;
						bool found=false;
						int index=-1;
						for (int i=0;i<count;i++){
							if (podatci[i].cijena==pod3){
								found=true;
								index=i;
							}
						}
						if (found){
							cout<<podatci[index].ime<<" se nalazi na "<<index+1<<". mjestu i cijelukupni podatci koje obuhvaca su: \n"<<"|-------------------------------------------------------------------------|\n| "<<podatci[index].ime<<" | "<<podatci[index].cijena<<" | "<<podatci[index].godine<<" | "<<podatci[index].kvaliteta<<" |\n|-------------------------------------------------------------------------|\n";
						}
						else if(!found) cout<<"nazalost to se ne nalazi u bazi podataka!\n";
						if (malim(pod1)=="natrag"){
							cout<<"idemo natrag!\n";
							break;
						}
						else{
							cout<<"pogresan unos, pokusajte ponovo!\n";
							continue;
						}
					} while (true);
				}
				else if (malim(odabir2)=="3"||malim(odabir2)=="godina"){				
					do{
						cout<<"unesite koja je godina koju trazite od podataka, ukoliko se zelite vratiti upisite natrag: ";
						cin>>pod2;
						bool found=false;
						int index=-1;
						for (int i=0;i<count;i++){
							if (podatci[i].godine==pod2){
								found=true;
								index=i;
							}
						}
						if (found){
							cout<<podatci[index].ime<<" se nalazi na "<<index+1<<". mjestu i cijelukupni podatci koje obuhvaca su: \n"<<"|-------------------------------------------------------------------------|\n| "<<podatci[index].ime<<" | "<<podatci[index].cijena<<" | "<<podatci[index].godine<<" | "<<podatci[index].kvaliteta<<" |\n|-------------------------------------------------------------------------|\n";
						}
						else if(!found) cout<<"nazalost to se ne nalazi u bazi podataka!\n";
						if (malim(pod1)=="natrag"){
							cout<<"idemo natrag!\n";
							break;
						}
						else{
							cout<<"pogresan unos, pokusajte ponovo!\n";
							continue;
						}
					} while (true);
				}
				else if (malim(odabir2)=="4"||malim(odabir2)=="kvaliteta"){				
					do{
						cout<<"unesite koja je kvaliteta koju trazite od podataka, ukoliko se zelite vratiti upisite natrag: ";
						cin>>pod3;
						bool found=false;
						int index=-1;
						for (int i=0;i<count;i++){
							if (podatci[i].kvaliteta==pod3){
								found=true;
								index=i;
							}
						}
						if (found){
							cout<<podatci[index].ime<<" se nalazi na "<<index+1<<". mjestu i cijelukupni podatci koje obuhvaca su: \n"<<"|-------------------------------------------------------------------------|\n| "<<podatci[index].ime<<" | "<<podatci[index].cijena<<" | "<<podatci[index].godine<<" | "<<podatci[index].kvaliteta<<" |\n|-------------------------------------------------------------------------|\n";
						}
						else if(!found) cout<<"nazalost to se ne nalazi u bazi podataka!\n";
						if (malim(pod1)=="natrag"){
							cout<<"idemo natrag!\n";
							break;
						}
						else{
							cout<<"pogresan unos, pokusajte ponovo!\n";
							continue;
						}
					} while (true);
				}
				else if (malim(odabir2)=="5"||malim(odabir2)=="natrag"){
					cout<<"u redu, vracamo se!\n";
					break;
				}
				else{
					cout<<"pogresan unos, pokusajte ponovo!\n";
					continue;
				}
			} while (true);
		}
		else if (malim(odabir1)=="5"||malim(odabir1)=="pohrana"){
			do{
				cout<<"zelite li pohraniti podatke u bazu podataka?: ";
				cin>>odabir2;
				if (malim(odabir2)=="da"){
					spremiuBAZU(podatci,count,"baza.txt");
				}
				else if (malim(odabir2)=="ne"){
					cout<<"u redu, idemo natrag!\n";
					break;
				}
				else{
					cout<<"pogresan unos, pokusajte ponovo!\n";
					continue;
				}
				break;		
			} while (true);
		}
		else if (malim(odabir1)=="6"||malim(odabir1)=="izlaz") {
			do{
				cout<<"jeste li sigurni da zelite izaci?: ";
				cin>>pod1;
				if (malim(pod1)=="da"){
					cout<<"u redu, dovidenja!\n";
					return 0;
				}
				else if (malim(pod1)=="ne"){
					cout<<"u redu, idemo natrag!\n";
					break;
				}
				else{
					cout<<"pogresan unos, pokusajte ponovo!\n";
					continue;
				}
			} while (true);
		}
		else{
			cout<<"pogresan unos, pokusajte ponovo!\n";
			continue;
		}
	} while (true);
	system("pause");
}
