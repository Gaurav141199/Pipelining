#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

typedef struct IFIDState {
    string instruction;
    int nextPc;
} IFIDState;

typedef struct IDEXState {
    string instruction;
    int nextPc;
    int readReg1;
    int readReg2;
    int destReg;
    int offset;
} IDEXState;

typedef struct EXMEMState {
    string instruction;
    int address;
    int value;
    int destReg;
    int nextPc;
} EXMEMState;

typedef struct MEMWBState {
    string instruction;
    int write;
    int nextPc;
    int destReg;
} MEMWBState;

typedef struct WBENDState {
    string instruction;
    int write;
    int nextPc;
    int destReg;
} WBENDState;

typedef struct state {
    int pc;
    string instMemory[4096];
    string dataMemory[4096];
    int registers[32];
    int numMemory;
    IFIDState IFID;
    IDEXState IDEX;
    EXMEMState EXMEM;
    MEMWBState MEMWB;
    WBENDState WBEND;
    int cycles; /* number of cycles run so far */
} stateType;


 int registers[32]={0};
 string memory[4096];
 int pc=0;


string hit_miss(float x){
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	cout<<r<<"\n";
	if(r<x) return "HIT";
	else return "MISS";
}

//string TypeofInst(string opcode);


vector<string> getInp(string input){
	vector<string> array;
	stringstream ss(input);
	string tok;
	while(getline(ss,tok,' ')){
		array.push_back(tok);
	}
	return array;
}

vector<string> lbrackSep(string input){
	vector<string> array;
	stringstream ss(input);
	string tok;
	while(getline(ss,tok,'(')){
		array.push_back(tok);
	}
	return array;
}

vector<string> rbrackSep(string input){
	vector<string> array;
	stringstream ss(input);
	string tok;
	while(getline(ss,tok,')')){
		array.push_back(tok);
	}
	return array;
}

string decToBinary(int n)
{
    int binaryNum[32];
    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    string result="";
    for (int j = i - 1; j >= 0; j--)
        result.append(to_string(binaryNum[j]));
    return result;
}

string decToBinaryReg(int n)
{
    int binaryNum[32];
    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    string result="";
    if(i==4) result="0";
    if(i==3) result="00";
    if(i==2) result="000";
    if(i==1) result="0000";
    if(i==0) result="00000";

    for (int j = i - 1; j >= 0; j--)
        result.append(to_string(binaryNum[j]));
    return result;
}

string decToBinary16(int n)
{
    int binaryNum[16]={0};
    int i = 15;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i--;
    }
    string result="";
    for (int j = 0; j <16 ; j++)
        result.append(to_string(binaryNum[j]));
    return result;
}

string decToBinary32(int n)
{
    int binaryNum[32]={0};
    int i = 31;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i--;
    }
    string result="";
    for (int j = 0; j <32 ; j++)
        result.append(to_string(binaryNum[j]));
    return result;
}

string decToBinary26(int n)
{
    int binaryNum[26]={0};
    int i = 25;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i--;
    }
    string result="";
    for (int j = 0; j <26 ; j++)
        result.append(to_string(binaryNum[j]));
    return result;
}

int binaryToDec(string n)
{
    string num = n;
    int dec_value = 0;
    int base = 1;
    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    return dec_value;
}

int mapreg(string name){
	if(name.compare("$zero")==0) return 0;
	else if(name.compare("$at")==0) return 1;
	else if(name.compare("$v0")==0) return 2;
	else if(name.compare("$v1")==0) return 3;
	else if(name.compare("$a0")==0) return 4;
	else if(name.compare("$a1")==0) return 5;
	else if(name.compare("$a2")==0) return 6;
	else if(name.compare("$a3")==0) return 7;
	else if(name.compare("$t0")==0) return 8;
	else if(name.compare("$t1")==0) return 9;
	else if(name.compare("$t2")==0) return 10;
	else if(name.compare("$t3")==0) return 11;
	else if(name.compare("$t4")==0) return 12;
	else if(name.compare("$t5")==0) return 13;
	else if(name.compare("$t6")==0) return 14;
	else if(name.compare("$t7")==0) return 15;
	else if(name.compare("$s0")==0) return 16;
	else if(name.compare("$s1")==0) return 17;
	else if(name.compare("$s2")==0) return 18;
	else if(name.compare("$s3")==0) return 19;
	else if(name.compare("$s4")==0) return 20;
	else if(name.compare("$s5")==0) return 21;
	else if(name.compare("$s6")==0) return 22;
	else if(name.compare("$s7")==0) return 23;
	else if(name.compare("$t8")==0) return 24;
	else if(name.compare("$t9")==0) return 25;
	else if(name.compare("$k0")==0) return 26;
	else if(name.compare("$k1")==0) return 27;
	else if(name.compare("$gp")==0) return 28;
	else if(name.compare("$sp")==0) return 29;
	else if(name.compare("$fp")==0) return 30;
	else if(name.compare("$ra")==0) return 31;
	else return 0;
}

string to_binary(vector<string> instr){
	string temp="";
	if(instr[0].compare("add")==0 || instr[0].compare("sub")==0){
		temp.append("000000");
		string rd=decToBinaryReg(mapreg(instr[1]));
		string rs=decToBinaryReg(mapreg(instr[2]));
		string rt=decToBinaryReg(mapreg(instr[3]));
		temp.append(rs);
		temp.append(rt);
		temp.append(rd);
		temp.append("00000");
		if(instr[0].compare("add")==0) temp.append("100000");
		else temp.append("100010");
		return temp;
	}
	else if(instr[0].compare("sll")==0 || instr[0].compare("srl")==0){
		temp.append("000000");
		string rd=decToBinaryReg(mapreg(instr[1]));
		string rt=decToBinaryReg(mapreg(instr[2]));
		string sa=decToBinaryReg(stoi(instr[3]));
		temp.append("00000");
		temp.append(rt);
		temp.append(rd);
		temp.append(sa);
		if(instr[0].compare("sll")==0) temp.append("000000");
		else temp.append("000010");
		return temp;
	}
	else if(instr[0].compare("lw")==0 || instr[0].compare("sw")==0){
		if(instr[0].compare("lw")==0) temp.append("100011");
		else temp.append("101011");
		vector<string> arr=lbrackSep(instr[2]);
		vector<string> arr2=rbrackSep(arr[1]);
		temp.append(decToBinaryReg(mapreg(arr2[0])));
		temp.append(decToBinaryReg(mapreg(instr[1])));
		temp.append(decToBinary16(stoi(arr[0])));
		return temp;
	}
	else if(instr[0].compare("j")==0){
		temp.append("000010");
		temp.append(decToBinary26(stoi(instr[1])));
		return temp;
	}
	else if(instr[0].compare("jal")==0){
		temp.append("000011");
		temp.append(decToBinary26(stoi(instr[1])));
		return temp;
	}
	else if(instr[0].compare("jr")==0){
		temp.append("00000011111000000000000000001000");
		return temp;
	}
	else if(instr[0].compare("beq")==0){
		temp.append("000100");
		string rs=decToBinaryReg(mapreg(instr[1]));
		string rt=decToBinaryReg(mapreg(instr[2]));
		temp.append(rs);
		temp.append(rt);
		temp.append(decToBinary16(stoi(instr[3])));
		return temp;
	}
	else if(instr[0].compare("bne")==0){
		temp.append("000101");
		string rs=decToBinaryReg(mapreg(instr[1]));
		string rt=decToBinaryReg(mapreg(instr[2]));
		temp.append(rs);
		temp.append(rt);
		temp.append(decToBinary16(stoi(instr[3])));
		return temp;
	}
	else if(instr[0].compare("exit")==0){
		temp.append("11111111111111111111111111111111");
		return temp;
	}
	else return temp;
}


IFIDState initialiseIFID(){
	IFIDState ifid;
	ifid.instruction="00000000000000000000000000000000";
	ifid.nextPc=0;
	return ifid;
}

IDEXState initialiseIDEX(){
	IDEXState idex;
	idex.instruction="00000000000000000000000000000000";
	idex.nextPc=0;
	idex.readReg1=0;
	idex.readReg2=0;
	idex.destReg=0;
	idex.offset=0;
	return idex;
}

EXMEMState initialiseEXMEM(){
	EXMEMState exem;
	exem.instruction="00000000000000000000000000000000";
	exem.address=0;
	exem.value=0;
	exem.destReg=0;
  exem.nextPc=0;
	return exem;
}

MEMWBState initialiseMEMWB(){
	MEMWBState memwb;
	memwb.instruction="00000000000000000000000000000000";
	memwb.write=0;
  memwb.nextPc=0;
  memwb.destReg=0;
	return memwb;
}

WBENDState initialiseWBEND(){
	WBENDState wbend;
	wbend.instruction="00000000000000000000000000000000";
	wbend.write=0;
	return wbend;
}

stateType initialiseState(){
	stateType state;
	state.pc=0;
	int l=0;
	while(l < 32) state.registers[l++]=0;
	int k=0;
	while(k < 4096) {
		state.instMemory[k]="00000000000000000000000000000000";
		state.dataMemory[k]="00000000000000000000000000000000";
		k++;
	}
	state.numMemory=0;
	state.IFID=initialiseIFID();
	state.IDEX=initialiseIDEX();
	state.EXMEM=initialiseEXMEM();
	state.MEMWB=initialiseMEMWB();
	state.WBEND=initialiseWBEND();
	state.cycles=0;
	return state;
}

void print_state(stateType state){
	cout<<"----------------------------------------------------------------------\n";
	cout<<"\nSTART PRINTING\npc:"<<state.pc<<"\n";
	cout<<"IFID:\n";
	cout<<"instruction->" <<state.IFID.instruction<<"\n";
	cout<<"IDEX:\n";
	cout<<"instruction->"<<state.IDEX.instruction<<"\n";
	cout<<"EXMEM:\n";
	cout<<"instruction->"<<state.EXMEM.instruction<<"\n";
	cout<<"MEMWB:\n";
	cout<<"instruction->"<<state.MEMWB.instruction<<"\n";
	cout<<"WBEND:\n";
	cout<<"instruction->"<<state.WBEND.instruction<<"\n";
	cout<<"ENDEX\n";
	cout<<"----------------------------------------------------------------------\n";
}

string opcode(string instr){
	printf("\033[0;31m");
	if(instr.substr(0,6).compare("000000")==0 && instr!="00000000000000000000000000000000"){
		if(instr.substr(26,6).compare("100000")==0){	//add
			cout<<"add\n";
			printf("\033[0m");
			return "add";
		}
		else if(instr.substr(26,6).compare("100010")==0){	//sub
			cout<<"sub\n";
			printf("\033[0m");
			return "sub";
		}
		else if(instr.substr(26,6).compare("000010")==0){	//srl
			cout<<"srl\n";
			printf("\033[0m");
			return "srl";
		}
		else if(instr.substr(26,6).compare("000000")==0){	//sll
			cout<<"sll\n";
			printf("\033[0m");
			return "sll";
		}
		else if(instr.substr(26,6).compare("001000")==0){	//jr
			cout<<"jr\n";
			printf("\033[0m");
			return "jr";
		}
		else return "NOOP";
	}
	else if(instr.substr(0,6).compare("100011")==0){	//lw
		cout<<"lw\n";
		printf("\033[0m");
		return "lw";
	}
	else if(instr.substr(0,6).compare("101011")==0){	//sw
		cout<<"sw\n";
		printf("\033[0m");
		return "sw";
	}
	else if(instr.substr(0,6).compare("000010")==0){	//j
		cout<<"j\n";
		printf("\033[0m");
		return "j";
	}
	else if(instr.substr(0,6).compare("000011")==0){	//jal
		cout<<"jal\n";
		printf("\033[0m");
		return "jal";
	}
	else if(instr.substr(0,6).compare("000100")==0){	//beq
		cout<<"beq\n";
		printf("\033[0m");
		return "beq";
	}
	else if(instr.substr(0,6).compare("000101")==0){	//bne
		cout<<"bne\n";
		printf("\033[0m");
		return "bne";
	}
	else if(instr.substr(0,6).compare("111111")==0){	//exit
		cout<<"exit\n";
		printf("\033[0m");
		return "exit";
	}
	else if(instr=="00000000000000000000000000000000"){	//noop
		cout<<"NOOP\n";printf("\033[0m");
		return "NOOP";
	}
	else return "NOOP";
}

bool check_lw(string A){
	if(A.substr(0,6).compare("100011")==0)return true;
	return false;
}

int main() {
	stateType state=initialiseState();
  	stateType newState=initialiseState();
	state.pc=0;
	int k=0;
	while(k < 4096) {
		state.instMemory[k]="00000000000000000000000000000000";
		state.dataMemory[k]="00000000000000000000000000000000";
		k++;
	}

	ifstream infile;
	infile.open("input.txt");
	string input;
	int noOfIns=0;
	while(getline(infile, input)){
		vector<string> instruction=getInp(input);
		string ins=to_binary(instruction);
		state.instMemory[noOfIns]=ins;
		state.dataMemory[noOfIns]=ins;
		noOfIns++;
	}
	srand(time(0));

	int instruction_count = 0;

	state.registers[9] = 5;
	
	state.registers[10] = 10;
	
	state.registers[11] = 5;

	state.dataMemory[110]="00000000000000000000000000000100";
	float probab;
	int delay;
	cout<<"Enter probability of HIT\n";
	cin>>probab;
	cout<<"Enter cycle delay\n";
	cin>>delay;



	int i=0;
	while(state.WBEND.instruction.compare("11111111111111111111111111111111") != 0) {

		printf("\033[1;32m");
		cout<<"memory";
		printf("\033[0m");

		printf("\033[1;34m");
		cout<<"["<<i<<"]: "; 
		printf("\033[0m");

		printf("\033[0;33m");
		cout<<state.instMemory[i]<<"  ";
		printf("\033[0m");

		opcode(state.instMemory[i]);
		
		if(hit_miss(probab) == "MISS") state.cycles += delay;

		//setting the variables of working state
		state.pc=i;
    	state.cycles++;
    	/*start executing*/

		//setting up WBEND for the working state
    state.WBEND.instruction=newState.MEMWB.instruction;
    state.WBEND.nextPc=newState.MEMWB.nextPc;
    if((state.WBEND.instruction).substr(0,6).compare("000000")==0 && state.WBEND.instruction!="00000000000000000000000000000000"){
    	instruction_count++;
      if((state.WBEND.instruction).substr(26,6).compare("100000")==0){	//add
        state.registers[newState.MEMWB.destReg]=newState.MEMWB.write;
        i++;
        cout<<"executing add: Value stored in "<<newState.MEMWB.destReg<<"="<<newState.MEMWB.write<<"\n";
      }
      else if((state.WBEND.instruction).substr(26,6).compare("100010")==0){	//sub
        state.registers[newState.MEMWB.destReg]=newState.MEMWB.write;
        i++;
        cout<<"executing sub: Value stored in "<<newState.MEMWB.destReg<<"="<<newState.MEMWB.write<<"\n";
      }
      else if((state.WBEND.instruction).substr(26,6).compare("000010")==0){	//srl
        state.registers[newState.MEMWB.destReg]=newState.MEMWB.write;
        i++;
        cout<<"executing srl: Value stored in "<<newState.MEMWB.destReg<<"="<<newState.MEMWB.write<<"\n";
      }
      else if((state.WBEND.instruction).substr(26,6).compare("000000")==0){	//sll
        state.registers[newState.MEMWB.destReg]=newState.MEMWB.write;
        i++;
        cout<<"executing sll: Value stored in "<<newState.MEMWB.destReg<<"="<<newState.MEMWB.write<<"\n";
      }
      else if((state.WBEND.instruction).substr(26,6).compare("001000")==0){	//jr
        state.IFID.instruction="00000000000000000000000000000000";
        state.IDEX.instruction="00000000000000000000000000000000";
        state.EXMEM.instruction="00000000000000000000000000000000";
        state.MEMWB.instruction="00000000000000000000000000000000";
        state.WBEND.instruction="00000000000000000000000000000000";
        i=state.registers[31];
        newState = state;
        cout<<"executing jr\n";
        print_state(state);
        continue;
      }
    }
    else if((state.WBEND.instruction).substr(0,6).compare("100011")==0){	//lw
      state.registers[newState.MEMWB.destReg]=newState.MEMWB.write;
      i++;
      cout<<"executing lw: Value stored in memory="<<newState.MEMWB.write<<"\n";
    }
    else if((state.WBEND.instruction).substr(0,6).compare("101011")==0){	//sw
      state.WBEND.instruction=newState.MEMWB.instruction;
      i++;
      cout<<"executing sw: Value stored in "<<"\n";
    }
    else if((state.WBEND.instruction).substr(0,6).compare("000010")==0){	//j
      i=newState.MEMWB.write;
      state.IFID.instruction="00000000000000000000000000000000";
      state.IDEX.instruction="00000000000000000000000000000000";
      state.EXMEM.instruction="00000000000000000000000000000000";
      state.MEMWB.instruction="00000000000000000000000000000000";
      state.WBEND.instruction="00000000000000000000000000000000";
      newState=state;
      cout<<"executing j: "<<i<<"\n";
      print_state(state);
      continue;
    }
    else if((state.WBEND.instruction).substr(0,6).compare("000011")==0){	//jal
      state.registers[31]=i+1-4;
      i=newState.MEMWB.write;
      state.IFID.instruction="00000000000000000000000000000000";
      state.IDEX.instruction="00000000000000000000000000000000";
      state.EXMEM.instruction="00000000000000000000000000000000";
      state.MEMWB.instruction="00000000000000000000000000000000";
      state.WBEND.instruction="00000000000000000000000000000000";
      newState = state;
      cout<<"executing jal: "<<i<<"\n";
      print_state(state);
      continue;
    }
    else if((state.WBEND.instruction).substr(0,6).compare("000100")==0){	//beq
      if(newState.MEMWB.write != -1){
		    i = newState.MEMWB.write;
		    state.IFID.instruction="00000000000000000000000000000000";
		    state.IDEX.instruction="00000000000000000000000000000000";
		    state.EXMEM.instruction="00000000000000000000000000000000";
		    state.MEMWB.instruction="00000000000000000000000000000000";
		    state.WBEND.instruction="00000000000000000000000000000000";
		    newState = state;
		    cout<<"Executing beq: "<<i<<"\n";
		    print_state(state);
	  		continue;
	  	}
	  	else {
	  		cout<<"Executing :- Not branched in beq\n";
	  		i++;
	  	}
    }
    else if((state.WBEND.instruction).substr(0,6).compare("000101")==0){	//bne
      if(newState.MEMWB.write != -1){
		    i= newState.MEMWB.write;
		    cout<<i<<"\n";
		    state.IFID.instruction="00000000000000000000000000000000";
		    state.IDEX.instruction="00000000000000000000000000000000";
		    state.EXMEM.instruction="00000000000000000000000000000000";
		    state.MEMWB.instruction="00000000000000000000000000000000";
		    state.WBEND.instruction="00000000000000000000000000000000";
		    newState = state;
		    cout<<"Executing bne: "<<i<<"\n";
		    print_state(state);
		    continue;
		}
		else {
			cout<<"Executing :- No branching in bne\n";
			i++;
		}
    }
    else i++;


    //settting up MEMWB for working state
    //memwb has instruction nextPc Write
    state.MEMWB.instruction=newState.EXMEM.instruction;
    state.MEMWB.nextPc=newState.EXMEM.nextPc;
    if((state.MEMWB.instruction).substr(0,6).compare("000000")==0){
      if((state.MEMWB.instruction).substr(26,6).compare("100000")==0){	//add
        state.MEMWB.destReg=newState.EXMEM.destReg;
        state.MEMWB.write=newState.EXMEM.value;
      }
      else if((state.MEMWB.instruction).substr(26,6).compare("100010")==0){	//sub
        state.MEMWB.destReg=newState.EXMEM.destReg;
        state.MEMWB.write=newState.EXMEM.value;
      }
      else if((state.MEMWB.instruction).substr(26,6).compare("000010")==0){	//srl
        state.MEMWB.destReg=newState.EXMEM.destReg;
        state.MEMWB.write=newState.EXMEM.value;
      }
      else if((state.MEMWB.instruction).substr(26,6).compare("000000")==0){	//sll
        state.MEMWB.destReg=newState.EXMEM.destReg;
        state.MEMWB.write=newState.EXMEM.value;
      }
      else if((state.MEMWB.instruction).substr(26,6).compare("001000")==0){	//jr
        state.MEMWB.instruction=newState.EXMEM.instruction;
      }
    }
    else if((state.MEMWB.instruction).substr(0,6).compare("100011")==0){	//lw
      state.MEMWB.destReg=newState.EXMEM.destReg;
      state.MEMWB.write=binaryToDec(state.dataMemory[newState.EXMEM.address]);
    }
    else if((state.MEMWB.instruction).substr(0,6).compare("101011")==0){	//sw
      state.MEMWB.destReg=newState.IDEX.destReg;
      state.dataMemory[newState.EXMEM.address]=decToBinary32(newState.registers[newState.EXMEM.destReg]);
    }
    else if((state.MEMWB.instruction).substr(0,6).compare("000010")==0){	//j
      state.MEMWB.write=newState.EXMEM.value;
    }
    else if((state.MEMWB.instruction).substr(0,6).compare("000011")==0){	//jal
      state.MEMWB.write=newState.EXMEM.value;
    }
    else if((state.MEMWB.instruction).substr(0,6).compare("000100")==0){	//beq
      state.MEMWB.write=newState.EXMEM.address;
    }
    else if((state.MEMWB.instruction).substr(0,6).compare("000101")==0){	//bne
      state.MEMWB.write=newState.EXMEM.address;
    }


    //setting up the EXMEM for the working state
    state.EXMEM.instruction= newState.IDEX.instruction;
    state.EXMEM.nextPc=newState.IDEX.nextPc;
    if((state.EXMEM.instruction).substr(0,6).compare("000000")==0){
      if((state.EXMEM.instruction).substr(26,6).compare("100000")==0){	//add

      	if(check_lw(newState.EXMEM.instruction) && (newState.IDEX.readReg1 == newState.EXMEM.destReg || newState.IDEX.readReg2 == newState.EXMEM.destReg)){
      		cout<<"Stalling due to LW.\n";
      		state.EXMEM.instruction = "";
      		state.EXMEM.destReg = -1;
      		state.EXMEM.value = 0;
      		state.EXMEM.address = 0;
      		state.cycles++;
      		newState = state;
      		i--;
      		print_state(state);
      		continue;
      	}else{
	      	if(newState.EXMEM.destReg == newState.IDEX.readReg1){
	      		if(newState.IDEX.readReg1 == newState.IDEX.readReg2)state.EXMEM.value = state.MEMWB.write*2;
	      		else state.EXMEM.value = state.MEMWB.write + state.registers[newState.IDEX.readReg2];
	      		cout<<"the val stored is "<<state.EXMEM.value<<"\n";
	      		state.EXMEM.destReg = newState.IDEX.destReg;
	      	}
	      	else if (newState.EXMEM.destReg == newState.IDEX.readReg2){
	      		state.EXMEM.value = state.MEMWB.write + state.registers[newState.IDEX.readReg1];
	      		state.EXMEM.destReg = newState.IDEX.destReg;
	      	}else {
		        state.EXMEM.value=state.registers[newState.IDEX.readReg1]+state.registers[newState.IDEX.readReg2];
		        state.EXMEM.destReg=newState.IDEX.destReg;
		    }
		}
      }
      else if((state.EXMEM.instruction).substr(26,6).compare("100010")==0){	//sub
      	if(check_lw(newState.EXMEM.instruction) && (newState.IDEX.readReg1 == newState.EXMEM.destReg || newState.IDEX.readReg2 == newState.EXMEM.destReg)){
      		cout<<"Stalling due to LW.\n";
      		state.EXMEM.instruction = "";
      		state.EXMEM.destReg = -1;
      		state.EXMEM.value = 0;
      		state.EXMEM.address = 0;
      		state.cycles++;
      		newState = state;
      		i--;
      		print_state(state);
      		continue;
      	}else{
	      	if(newState.EXMEM.destReg == newState.IDEX.readReg1){
	      		if(newState.IDEX.readReg1 == newState.IDEX.readReg2)state.EXMEM.value = 0;
	      		else state.EXMEM.value = state.MEMWB.write - state.registers[newState.IDEX.readReg2];
	        	state.EXMEM.destReg = newState.IDEX.destReg;
	      	}else if (newState.EXMEM.destReg == newState.IDEX.readReg2){
	      		state.EXMEM.value = state.registers[newState.IDEX.readReg1] - state.MEMWB.write;
	        	state.EXMEM.destReg = newState.IDEX.destReg;
	      	}else{
		        state.EXMEM.value=state.registers[newState.IDEX.readReg1]-state.registers[newState.IDEX.readReg2];
		        state.EXMEM.destReg=newState.IDEX.destReg;
		    }
		}
      }
      else if((state.EXMEM.instruction).substr(26,6).compare("000010")==0){	//srl
      	//the readReg2 has the value of base register
      	if(check_lw(newState.EXMEM.instruction) && newState.IDEX.readReg2 == newState.EXMEM.destReg){
      		cout<<"Stalling due to LW.\n";
      		state.EXMEM.instruction = "";
      		state.EXMEM.destReg = -1;
      		state.EXMEM.value = 0;
      		state.EXMEM.address = 0;
      		state.cycles++;
      		newState = state;
      		i--;
      		print_state(state);
      		continue;
      	}else{
	      	if(newState.IDEX.readReg2 == newState.EXMEM.destReg){
	      		state.EXMEM.value = state.MEMWB.write >> newState.IDEX.readReg1;
	      		state.EXMEM.destReg = newState.IDEX.destReg;
	      	}else {
	      		state.EXMEM.value = state.registers[newState.IDEX.readReg2] >> newState.IDEX.readReg1;
	        	state.EXMEM.destReg=newState.IDEX.destReg;
	      	}
	    }        
      }
      else if((state.EXMEM.instruction).substr(26,6).compare("000000")==0){	//sll
      	if(check_lw(newState.EXMEM.instruction) && newState.IDEX.readReg2 == newState.EXMEM.destReg){
      		cout<<"Stalling due to LW.\n";
      		state.EXMEM.instruction = "";
      		state.EXMEM.destReg = -1;
      		state.EXMEM.value = 0;
      		state.EXMEM.address = 0;
      		state.cycles++;
      		newState = state;
      		i--;
      		print_state(state);
      		continue;
      	}else{
	      	if(newState.IDEX.readReg2 == newState.EXMEM.destReg){
	      		state.EXMEM.value = state.MEMWB.write << newState.IDEX.readReg1;
	      		state.EXMEM.destReg = newState.IDEX.destReg;
	      	}else {
	      		state.EXMEM.value = state.registers[newState.IDEX.readReg2] << newState.IDEX.readReg1;
	        	state.EXMEM.destReg=newState.IDEX.destReg;
	      	}
	    }
      }
      else if((state.EXMEM.instruction).substr(26,6).compare("001000")==0){	//jr
        state.IDEX.instruction=newState.IDEX.instruction;
      }
    }
    else if((state.EXMEM.instruction).substr(0,6).compare("100011")==0){	//lw
   		if(check_lw(newState.EXMEM.instruction) && state.IDEX.readReg1 == newState.EXMEM.destReg){
   			cout<<"Stalling due to LW.\n";
      		state.EXMEM.instruction = "";
      		state.EXMEM.destReg = -1;
      		state.EXMEM.value = 0;
      		state.EXMEM.address = 0;
      		state.cycles++;
      		newState = state;
      		i--;
      		print_state(state);
      		continue;
   		}else{
	    	state.EXMEM.address=state.registers[state.IDEX.readReg1]+newState.IDEX.offset;
	    	state.EXMEM.destReg=newState.IDEX.destReg;
	    }
    }
    else if((state.EXMEM.instruction).substr(0,6).compare("101011")==0){	//sw
    	if(check_lw(newState.EXMEM.instruction) && state.IDEX.readReg1 == newState.EXMEM.destReg){
   			cout<<"Stalling due to LW.\n";
      		state.EXMEM.instruction = "";
      		state.EXMEM.destReg = -1;
      		state.EXMEM.value = 0;
      		state.EXMEM.address = 0;
      		state.cycles++;
      		newState = state;
      		i--;
      		print_state(state);
      		continue;
   		}else{
	    	if(newState.EXMEM.destReg == newState.IDEX.readReg1){
	    		state.EXMEM.address = state.MEMWB.write + newState.IDEX.offset;
	    		state.EXMEM.destReg=newState.IDEX.destReg;
	    	}else{
		    	state.EXMEM.address=state.registers[newState.IDEX.readReg1]+newState.IDEX.offset;
		    	state.EXMEM.destReg=newState.IDEX.destReg;
		    }
		}
    }
    else if((state.EXMEM.instruction).substr(0,6).compare("000010")==0){	//j
      state.EXMEM.value=newState.IDEX.offset;
    }
    else if((state.EXMEM.instruction).substr(0,6).compare("000011")==0){	//jal
      state.EXMEM.value=newState.IDEX.offset;
    }
    else if((state.EXMEM.instruction).substr(0,6).compare("000100")==0){	//beq
      if(state.registers[newState.IDEX.readReg1] == state.registers[newState.IDEX.readReg2]){
		      state.EXMEM.address=newState.IDEX.offset;
		}
		    else state.EXMEM.address = -1;
    	}
    else if((state.EXMEM.instruction).substr(0,6).compare("000101")==0){	//bne
      if(state.registers[newState.IDEX.readReg1] != state.registers[newState.IDEX.readReg2]){
		      state.EXMEM.address = newState.IDEX.offset;
		}
		    else state.EXMEM.address = -1;
		}

    //setting up the IDEX for the working state
    state.IDEX.instruction=newState.IFID.instruction;
    state.IDEX.nextPc=newState.IFID.nextPc;
    if((state.IDEX.instruction).substr(0,6).compare("000000")==0){
      if((state.IDEX.instruction).substr(26,6).compare("100000")==0){		//for add
        state.IDEX.readReg1=binaryToDec((state.IDEX.instruction).substr(6,5));
        state.IDEX.readReg2=binaryToDec((state.IDEX.instruction).substr(11,5));
        state.IDEX.destReg=binaryToDec((state.IDEX.instruction).substr(16,5));
      }
      else if((state.IDEX.instruction).substr(26,6).compare("100010")==0){	//for sub
        state.IDEX.readReg1=binaryToDec((state.IDEX.instruction).substr(6,5));
        state.IDEX.readReg2=binaryToDec((state.IDEX.instruction).substr(11,5));
        state.IDEX.destReg=binaryToDec((state.IDEX.instruction).substr(16,5));
      }
      else if((state.IDEX.instruction).substr(26,6).compare("000010")==0){	//srl
        state.IDEX.readReg1=binaryToDec((state.IDEX.instruction).substr(21,5)); //readReg1 has shift value
        state.IDEX.readReg2=binaryToDec((state.IDEX.instruction).substr(11,5));
        state.IDEX.destReg=binaryToDec((state.IDEX.instruction).substr(16,5));
      }
      else if((state.IDEX.instruction).substr(26,6).compare("000000")==0){	//sll
        state.IDEX.readReg1=binaryToDec((state.IDEX.instruction).substr(21,5));	//readReg1 has shift value
        state.IDEX.readReg2=binaryToDec((state.IDEX.instruction).substr(11,5));
        state.IDEX.destReg=binaryToDec((state.IDEX.instruction).substr(16,5));
      }
      else if((state.IDEX.instruction).substr(26,6).compare("001000")==0){	//jr
        state.IDEX.instruction=state.IDEX.instruction;
      }
    }
    else if((state.IDEX.instruction).substr(0,6).compare("100011")==0){	//lw
      state.IDEX.readReg1=binaryToDec((state.IDEX.instruction).substr(6,5));	//has base register
      state.IDEX.destReg=binaryToDec((state.IDEX.instruction).substr(11,5));	
      state.IDEX.offset=binaryToDec((state.IDEX.instruction).substr(16,16));
    }
    else if((state.IDEX.instruction).substr(0,6).compare("101011")==0){	//sw
      state.IDEX.readReg1=binaryToDec((state.IDEX.instruction).substr(6,5));	//has base register
      state.IDEX.destReg=binaryToDec((state.IDEX.instruction).substr(11,5));	
      state.IDEX.offset=binaryToDec((state.IDEX.instruction).substr(16,16));
    }
    else if((state.IDEX.instruction).substr(0,6).compare("000010")==0){	//j
      state.IDEX.offset=binaryToDec((state.IDEX.instruction).substr(6,26));
      state.IDEX.readReg2=i;
    }
    else if((state.IDEX.instruction).substr(0,6).compare("000011")==0){	//jal
      state.IDEX.offset=binaryToDec((state.IDEX.instruction).substr(6,26));
    }
    else if((state.IDEX.instruction).substr(0,6).compare("000100")==0){	//beq
      state.IDEX.readReg1=binaryToDec((state.IDEX.instruction).substr(6,5));
      state.IDEX.readReg2=binaryToDec((state.IDEX.instruction).substr(11,5));
      state.IDEX.offset=binaryToDec((state.IDEX.instruction).substr(16,16));

    }
    else if((state.IDEX.instruction).substr(0,6).compare("000101")==0){	//bne
      state.IDEX.readReg1=binaryToDec((state.IDEX.instruction).substr(6,5));
      state.IDEX.readReg2=binaryToDec((state.IDEX.instruction).substr(11,5));
      state.IDEX.offset=binaryToDec((state.IDEX.instruction).substr(16,16));
    }

    
    //updating the IFID details in working state
		state.IFID.instruction= state.instMemory[i-1];
		state.IFID.nextPc= i-1;
    
    newState = state;

    print_state(state);

   	/*end executing*/		
	}

	float ipc = (double)instruction_count/(double)state.cycles;

	cout<<"total cycles = "<<state.cycles<<endl;
	cout<<"instruction per cycle = " <<ipc<<endl;
  	return 0;
 }
