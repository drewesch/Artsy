var memory;

fetch('./WASMcode.wasm').then(response =>
response.arrayBuffer()
).then(bytes => WebAssembly.instantiate(bytes, {
env: {
   printInt: function printInt(wVar) {
      document.write(wVar)
   },

   printFloat: function printFloat(wVar) {
      document.write(wVar)
   },

   printString: function printString(wVar) {
      document.write(String.fromCharCode(wVar))
   },

   newline: function newline() {
      var p = document.createElement('p');
      var t = document.createTextNode("\n");
      p.appendChild(t);
      document.body.appendChild(p);
   }
}
})
).then(results => {
instance = results.instance;
memory = instance.exports.pagememory;
instance.exports.main();
}).catch(console.error);