var memory;

fetch('./helloworld.wasm').then(response =>
response.arrayBuffer()
).then(bytes => WebAssembly.instantiate(bytes, {
env: {
   jsprint: function jsprint(byteOffset) {
      var s = '';
      var a = new Uint8Array(memory.buffer);
      for (var i = byteOffset; a[i]; i++) {
      s += String.fromCharCode(a[i]);
      }
      var p = document.createElement('p');
      var t = document.createTextNode(s);
      p.appendChild(t);
      document.body.appendChild(p);
   },

   newline: function newline() {
      var p = document.createElement('p');
      var t = document.createTextNode("\n");
      p.appendChild(t);
      document.body.appendChild(p);
   },

   writeconsole: function writeconsole(intVar) {
      document.write(intVar)
   }
}
})
).then(results => {
instance = results.instance;
memory = instance.exports.pagememory;
instance.exports.main();
}).catch(console.error);