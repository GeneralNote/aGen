#include <iostream>
#include <fstream>
#include <agen.h>

int main() {
	ag::Generator gen;
	
	// header - version
	gen.SetHeader(0, 1);

	/*
	size_t class_id = gen.AddObject("Animal");
	gen.AddProperty("Animal", "type");
	gen.AddProperty("Animal", "name");
	gen.AddProperty("Animal", "health");
	gen.AddMethod("Animal", "Animal", ag::Type::Void);	// constructor
	gen.AddMethod("Animal", "status", ag::Type::Void);	// dog.status();

	gen.Function.SetCurrent("Animal", "Animal");// constructor
		gen.Function.PushStack("Dog");
		gen.Function.SetMyProperty("type");		// this->type = "Dog"
		gen.Function.PushStack("Jeff");
		gen.Function.SetMyProperty("name");		// this->name = "Jeff"
		gen.Function.PushStack(100);
		gen.Function.SetMyProperty(health);		// this->health = 100

	gen.Function.SetCurrent("Animal", "status");
		gen.Function.PushStack("type = ");
		gen.Function.GetMyProperty("type");
		gen.Function.PushStack("; name = ");
		gen.Function.GetMyProperty("name");
		gen.Function.PushStack("; hp = ");
		gen.Function.GetMyProperty("health");
		gen.Function.PushStack(";\n");
		gen.Function.Call("print");

	gen.Function.Create("main", ag::Type::Int, {});

	gen.Function.SetCurrent("main");
		gen.Function.NewObject(class_id);		// Animal()
		gen.Function.SetLocal(0);				// loc0 = Animal();

		gen.Function.PushStack("Donna");		// "Donna"
		gen.Function.GetLocal(0);				// loc0 "Donna" 
		gen.Function.SetProperty("name");		// loc0.name = "Donna"
		gen.Function.SetLocal(0);

		gen.Function.GetLocal(0);				// loc0
		gen.Function.CallMethod("status", 0);	// loc0.status();

		gen.Function.NewObject(class_id);		// Animal()
		gen.Function.CallMethod("status", 0);	// Animal().status()

		gen.Function.PushNull();				// or gen.Function.NewObject(0);
		gen.Function.GetLocal(0);				// loc0 null
		gen.Function.Equal();					// loc0 == null
		gen.Function.Print("print", 1);			// print(loc0 == null);

		gen.Function.PushNull();
		gen.Function.SetLocal(0);				// loc0 = null
		gen.Function.PushNull();				// null
		gen.Function.GetLocal(0);				// loc0 null
		gen.Function.Equal();					// loc0 == null
		gen.Function.Print("print", 1);			// print(loc0 == null);

		gen.Function.PushStack(0);
		gen.Function.Return();					// return 0
		*/

	size_t nid = gen.AddGlobal("a");

	size_t cid = gen.AddObject("Vehicle");
		gen.AddProperty("Vehicle", "type");
		gen.AddProperty("Vehicle", "owner");

	gen.Function.Create("main", ag::Type::Int);
	gen.Function.Create("fib", ag::Type::Int, 1);

	gen.Function.SetCurrent("fib");
		gen.Function.GetArgument(0);
		gen.Function.PushStack(0);
		gen.Function.Equal();
		size_t& if1 = gen.Function.If(); // if (arg0 == 0)
			gen.Function.PushStack(0);
			gen.Function.Return();
		gen.Function.GetCurrentAddress(if1);

		gen.Function.GetArgument(0);
		gen.Function.PushStack(1);
		gen.Function.Equal();
		size_t& if2 = gen.Function.If(); // if (arg1 == 1)
			gen.Function.PushStack(1);
			gen.Function.Return();
		gen.Function.GetCurrentAddress(if2);

		gen.Function.GetArgument(0);
		gen.Function.PushStack(1);
		gen.Function.Subtract();
		gen.Function.CallReturn("fib", 1);

		gen.Function.GetArgument(0);
		gen.Function.PushStack(2);
		gen.Function.Subtract();
		gen.Function.CallReturn("fib", 1);

		gen.Function.Add();

		gen.Function.Return();


	gen.Function.SetCurrent("main");
		gen.Function.NewObject(cid);
		gen.Function.SetLocal(0);

		gen.Function.PushStack("Tank");
		gen.Function.SetProperty(0, "type");

		gen.Function.PushStack("Jeff");
		gen.Function.SetProperty(0, "owner");

		gen.Function.GetLocal(0);
		gen.Function.CallMethod("status", 0);
		gen.Function.PopStack(); // remove class from stack :(

		gen.Function.PushStack(10);
		gen.Function.NewArray(1);
		gen.Function.SetLocal(1);

		gen.Function.PushStack(3);		// 3
		gen.Function.PushStack(3);		// 3 3
		gen.Function.GetLocal(1);		// loc1 3 3
		gen.Function.PushStack(10);		// 10 loc1 3 3
		gen.Function.SetArrayElement();	// (loc1[3] = 10) 3
		gen.Function.GetArrayElement();	// (loc1[3] = 10)[3]
		gen.Function.Call("print", 1);	// print((loc1[3] = 10)[3]);

		gen.Function.GetGlobal(nid);
		gen.Function.CallReturn("fib", 1);
		gen.Function.Return();					// return 0
		
	ag::ByteCode bc = gen.Get();// get bytecode

	std::ofstream file("E:/aGen/test.bv", std::ios::out | std::ios::binary);
	file.write(reinterpret_cast<const char *>(bc.Get().data()), bc.Count());

	std::cout << "[end]" << std::endl;
	getchar();
	return 0;
}