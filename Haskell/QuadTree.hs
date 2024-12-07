{-# LANGUAGE DatatypeContexts #-}
data ( Eq a , Show a ) => QT a = C a | Q ( QT a ) ( QT a ) ( QT a ) ( QT a )
 deriving ( Eq , Show )


data Matrix a = Mat {
nexp :: Int ,
mat :: QT a
}


foldQuadTree _ acc (C a) = acc a
foldQuadTree f acc (Q x y z w) = f (foldQuadTree f acc x) (foldQuadTree f acc y) (foldQuadTree f acc z) (foldQuadTree f acc w)


zipWithQuadTree f (C x ) (C y ) = C $ f x y
zipWithQuadTree f (C l) (Q x y z w) = 
  let
    tl = zipWithQuadTree f (C l) x 
    tr = zipWithQuadTree f (C l) y 
    bl = zipWithQuadTree f (C l) z
    br = zipWithQuadTree f (C l) w 
  in Q tl tr bl br  
  
zipWithQuadTree f (Q x y z w) (C l)  = 
  let
   tl = zipWithQuadTree f x (C l)
   tr = zipWithQuadTree f y (C l)
   bl = zipWithQuadTree f z (C l)
   br = zipWithQuadTree f w (C l)
  in Q tl tr bl br 


zipWithQuadTree f (Q x y z w) (Q x1 y1 z1 w1) = 
  let 
   tl = zipWithQuadTree f x x1
   tr = zipWithQuadTree f y y1
   bl = zipWithQuadTree f z z1
   br = zipWithQuadTree f w w1
  in Q tl tr bl br

-- f che fa la moltiplicazione tra 2 QT
quadTreeMul' (C x) (C y)  = C $ x * y  

quadTreeMul' m2@(C x) (Q tl tr bl br) = 
  let 
   x2 = zipWithQuadTree (+) (quadTreeMul' m2 tl) (quadTreeMul' m2 bl)
   x3 = zipWithQuadTree (+) (quadTreeMul' m2 tr) (quadTreeMul' m2 br)
  in Q x2 x3 x2 x3 


quadTreeMul' (Q tl tr bl br) m2@(C x) = 
  let 
   x2 = zipWithQuadTree (+) (quadTreeMul' m2 tl) (quadTreeMul' m2 tr)
   x3 = zipWithQuadTree (+) (quadTreeMul' m2 bl) (quadTreeMul' m2 br)
  in Q x2 x2 x3 x3 

quadTreeMul' (Q nwA neA swA seA) (Q nwB neB swB seB) = 
   let
    x1 = zipWithQuadTree (+) (quadTreeMul' nwA nwB) (quadTreeMul' neA swB)
    x2 = zipWithQuadTree (+) (quadTreeMul' nwA neB) (quadTreeMul' neA seB)
    x3 = zipWithQuadTree (+) (quadTreeMul' swA nwB) (quadTreeMul' seA swB)
    x4 = zipWithQuadTree (+) (quadTreeMul' swA neB) (quadTreeMul' seA seB)
   in Q x1 x2 x3 x4

-- f che produce la trasposta di un QT
quadTranspose (C x) = C x
quadTranspose (Q tl tr bl br) = 
  let 
   tl' = quadTranspose tl
   tr' = quadTranspose tr
   bl' = quadTranspose bl
   br' = quadTranspose br
  in Q tl' bl' tr' br'


zipProva'' = 
  let 
    z = C 2  
    z' = C 4
    z'' = C 6
    z''' = C 8
    u = C 12
    u' = C 16 
    nwA = Q z z' z z' 
    neA = Q u u' u u'
    swA = Q z' z''' z' z'''
    seA = Q z'' z''' z'' z'''

    nwB = Q z z z' z' 
    neB = Q z' z' z''' z'''
    swB = Q u u u' u'
    seB = Q z'' z'' z''' z'''
  in quadTreeMul' (Q nwA neA swA seA) (Q nwB neB swB seB) 


--funzione per testare il numero di foglie (pixel) di un QT

howManyPixelsFold q = foldQuadTree (\x y z w -> 4 * max (max x y) (max z w)  ) (\x -> 1 ) q

--dato un QT genera un QuadTree Corrispondente
foldSimplify q = foldQuadTree simplifySupport  (\x -> C x) q 
  where
    simplifySupport  (C x) (C y) (C z) (C w)  |  x == y && y == z && z == w = C x
                                              |  otherwise = Q (C x) (C y) (C z) (C w)  
    simplifySupport tl tr bl br = Q tl tr bl br


-- dato un quadTree genero un QT che rappresenta immagine 
-- espande l'albero in modo da che tutti gli elementi della matrice siano presenti nelle foglie
-- dato una foglia la mappo in un QT con uno numero di foglie pari al numero di elementi della matrice in quel quadrante
quadDecompressed (Mat n (C x)) n1 = fdecompressionAusiliar (C x) n1  
  where
    fdecompressionAusiliar (C x) 0 = C x
    fdecompressionAusiliar (C x) n = 
      let
       x1 = fdecompressionAusiliar (C x) (n-1) 
       x2 = fdecompressionAusiliar (C x) (n-1)
       x3 = fdecompressionAusiliar (C x) (n-1)   
       x4 = fdecompressionAusiliar (C x) (n-1)
      in Q x1 x2 x3 x4

quadDecompressed (Mat n (Q tl tr bl br) ) n1 =  
   let
    x1 = quadDecompressed (Mat n tl) (n1-1)
    x2 = quadDecompressed (Mat n tr) (n1-1) 
    x3 = quadDecompressed (Mat n bl) (n1-1) 
    x4 = quadDecompressed (Mat n br) (n1-1)
   in Q x1 x2 x3 x4 

--test f di decompressione 
treeBis = let z = C 0; u = C 1; q = Q z u u u in quadDecompressed (Mat 2 q) 2 
treeBis' = let z = C 5; u = Q (C 1) (C 3) (C 6) (C 8) ; q = Q z u u z in quadDecompressed (Mat 2 q) 2 

treeBis'' = let z = C 8; u = C 16; q = Q z u u z in quadDecompressed (Mat 2 q) 2 


-- f di trasformazione che applica ad ogni elemento della matrice una trasformazione
fTransformation f (Mat n (C x)) idxstart _ = C $ f idxstart (2 ^ n) x
fTransformation f (Mat n (Q tl tr bl br)) idxstart idxend =
    let
     x1 = fTransformation f (Mat n tl) idxstart ( (idxstart + idxend) `div` 2)   
     x2 = fTransformation f (Mat n tr) ( (idxstart + idxend) `div` 2 + 1) idxend 
     x3 = fTransformation f (Mat n bl) idxstart (idxend`div` 2)  
     x4 = fTransformation f (Mat n br) ( (idxstart + idxend) `div` 2 + 1) idxend 
    in Q x1 x2 x3 x4

treeProva = fTransformation (\ x y z -> x + y + z) (Mat 2 treeBis) 1 4  

treeProva' = fTransformation (\ k m x -> div ( x*k ) m ) (Mat 2 treeBis'') 1 4  

weirdFunc f m@(Mat n q) =
  let
   qTransformed = fTransformation f (Mat n $ quadDecompressed  m n) 1 (2^n) 
   qMul = quadTreeMul' qTransformed $ quadTranspose  qTransformed 
  in  Mat n $ foldSimplify  qMul

treeTest = let f k m x = div (x*k) m in mat $ weirdFunc f (Mat 2  $ Q (C 8) (C 16) (C 16) (C 8) )
treeTest' = let f k m x = k + m + x in mat $ weirdFunc f (Mat 1  $  C 5)

treeTest'' = let f k m x = k + m + x; q = Q (C 5) (Q (C 1) (C 3) (C 6) (C 8)) (Q (C 32) (C 27) (C 45) (C 11)) (C 7) in mat $ weirdFunc f (Mat 2  $ q )

treeTest''' = let f k m x = k + m + x in mat $ weirdFunc f (Mat 0  $  C 8)

treeTest'''' = let f k m x = k + m + x; q = Q (C 5) (Q (C 1) (C 3) (C 6) (C 8)) (Q (C 32) (C 27) (C 45) (C 11)) (C 7) in mat $ weirdFunc f (Mat 3  $ q )

treeTest''''' = let f k m x = div (x*k) m in mat $ weirdFunc f (Mat 3  $  C 4)

--IMPORTANTE: solo alla fine ottengo il quadTree dal QT, tutte le operazioni lavorano su un QT!