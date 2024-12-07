| strumento | versione |
| --------- | -------- |
| BNFC      | 2.9.5    |
| Alex      | 3.5.1.0  |
| Happy     | 1.20.1.1 |
| GHC       | 9.4.8    |

Let's consider a tree representation with 3 kind of nodes, implemented with the following `Haskell type:`

```
 data Tree a b = Leaf b | Chain [Tree a b] | Repeat a (Tree a b)
```
Given in input a string of the following type:

```
3* ("aa" +"bb")+ "cc"+"dd"
```
We built a `Parser` (with relative `Lexer`) being able to recognize strings of the above type and produce in output a value of type `Tree Int String`.
With the above input, the output will be:

```
 Chain [Repeat 3 (Chain [Leaf "aa", Leaf "bb"]), Leaf "cc", Leaf "dd"]
```
