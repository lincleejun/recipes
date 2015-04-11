#lang plai-typed
;;function exp

;; function type definition
(define-type FunDefC
  [fdC (name : symbol) (arg : symbol) (body : ExprC)])

;; expression
(define-type ExprC
  [numC (n : number)]
  [idC (s : symbol)]
  [appC (fun : symbol) (arg : ExprC)]
  [plusC (l : ExprC) (r : ExprC)]
  [multC (l : ExprC) (r : ExprC)]
  [fdC (name : symbol) (arg : symbol) (body : ExprC)])

;; value
(define-type Value
  [numV (n : number)]
  [funV (name : symbol) (arg : symbol) (body : ExprC)])


;; substitution
(define (subst [what : ExprC] [for : symbol] [in : ExprC]) : ExprC
  (type-case ExprC in
    [numC (n) in]
    [idC (s) (cond
               [(symbol=? s for) what]
               [else in])]
    [appC (fun arg) (appC fun (subst what for arg))]
    [plusC (l r) (plusC (subst what for l)
                       (subst what for r))]
    [multC (l r) (multC (subst what for l)
                        (subst what for r))]))


(define (get-fundef [n : symbol] [fds : (listof FunDefC)]) : FunDefC
  (cond
    [(empty? fds) (error 'get-fundef "reference to undefined function")]
    [(cons? fds) (cond
                   [(equal? n (fdC-name (first fds))) (first fds)]
                   [else (get-fundef n (rest fds))])]))

;; env
(define-type Binding
 [bind (name : symbol) (val : number)])

(define-type-alias Env (listof Binding))
(define mt-env empty)
(define extend-env cons)

;; lookup
(define (lookup [for : symbol] [env : Env]) : number
  (cond
    [(empty? env) (error 'lookup "name not found")]
    [else (cond
            [(symbol=? for (bind-name (first env)))
             (bind-val (first env))]
            [else (lookup for (rest env))])]))



;; interpreter
(define (interp [expr : ExprC] [env : Env] [fds : (listof FunDefC)]) : number
  (type-case ExprC expr
    [numC (n) n]
    [idC (n) (lookup n env)]
    [appC (f a) (local ([define fd (get-fundef f fds)])
                  (interp (fdC-body fd)
                           (extend-env (bind (fdC-arg fd)
                                             (interp a env fds))
                                       mt-env)
                          fds))]
    
    [plusC (l r) (+ (interp l env fds) (interp r env fds))]
    [multC (l r) (* (interp l env fds) (interp r env fds))]))


;; testings
(test (interp (plusC (numC 10) (appC 'const5 (numC 10)))
                mt-env
                (list (fdC 'const5 '_ (numC 5))))
        15)

(test (interp (plusC (numC 10) (appC 'double (plusC (numC 1) (numC 2))))
                mt-env
                (list (fdC 'double 'x (plusC (idC 'x) (idC 'x)))))
        16)

(test (interp (plusC (numC 10) (appC 'quadruple (plusC (numC 1) (numC 2))))
                mt-env
                (list (fdC 'quadruple 'x (appC 'double (appC 'double (idC 'x))))
                      (fdC 'double 'x (plusC (idC 'x) (idC 'x)))))
        22)


;; test local variable x out of scope
(interp (appC 'f1 (numC 3))
          mt-env
          (list (fdC 'f1 'x (appC 'f2 (numC 4)))
                (fdC 'f2 'y (plusC (idC 'x) (idC 'y)))))

;;closure ???