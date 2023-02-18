var memory;

fetch('./WASMcode.wasm').then(response =>
response.arrayBuffer()
).then(bytes => WebAssembly.instantiate(bytes, {
env: {
   writeconsoleInt: function writeconsole(wVar) {
      document.write(wVar)
   },

   writeconsoleFloat: function writeconsole(wVar) {
      document.write(wVar)
   },

   writeconsoleString: function writeconsole(wVar) {
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