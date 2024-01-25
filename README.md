# BigInt-Library in C++
## How to create Share Library 
<p>In MAC OS: Int the repository where your file is stored</p>

<pre><code>
g++-11 -dynamiclib -o lbigint.dylib BigInt.cpp
g++-11 main.cpp -L/ lbigint.dylib
./a.out
</code></pre>

<p> Use your g++ compiler version instead od g++-11 </p>
