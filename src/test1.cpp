/**
 * from:
 *  http://stackoverflow.com/questions/11387015/calling-a-v8-javascript-function-from-c-with-an-argument
 */

#include <v8.h>
#include <iostream>
#include <string>

#include <stdlib.h>

using namespace v8;

int main(int argc, char* argv[]) {

// Create a stack-allocated handle scope.
HandleScope handle_scope;

// Create a new context.
Persistent<Context> context = Context::New();

//context->AllowCodeGenerationFromStrings(true);

// Enter the created context for compiling and
// running the hello world script.
Context::Scope context_scope(context);
Handle<String> source;
Handle<Script> script;
Handle<Value> result;


// Create a string containing the JavaScript source code.
source = String::New("function test_function() { var match = 0;if(arguments[0] == arguments[1]) { match = 1; } return match; }");

// Compile the source code.
script = Script::Compile(source);

// Run the script to get the result.
result = script->Run();
// Dispose the persistent context.
context.Dispose();

// Convert the result to an ASCII string and print it.
//String::AsciiValue ascii(result);
//printf("%s\n", *ascii);

Handle<v8::Object> global = context->Global();
Handle<v8::Value> value = global->Get(String::New("test_function"));
Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
Handle<Value> args[2];
Handle<Value> js_result;
int final_result;

args[0] = v8::String::New("1");
args[1] = v8::String::New("1");

js_result = func->Call(global, 2, args);
String::AsciiValue ascii(js_result);

final_result = atoi(*ascii);

if(final_result == 1) {

    std::cout << "Matched\n";

} else {

    std::cout << "NOT Matched\n";

}

return 0;

}