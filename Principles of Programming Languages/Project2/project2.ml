let validVarNames = ["a"; "b"; "c"; "d"; "e"; "f"; "g"; "h"; "i"; "j"; "k"; "l"; "m"; "n"; "o"; "p"; "q"; "r"; "s"; "t"; "u"; "v"; "w"; "x"; "y"; "z"];;

(* Partition Function *)
let partition (input: string list) (bound: string) : string list list =
  let rec partitionHelper acc currentPartition remaining =
    match remaining with
    | [] -> 
        if currentPartition = [] then List.rev acc
        else List.rev (List.rev currentPartition :: acc)
    | hd :: tl ->
        if hd = bound then
          if currentPartition = [] then 
            partitionHelper acc [] tl
          else 
            partitionHelper (List.rev currentPartition :: acc) [] tl
        else
          partitionHelper acc (hd :: currentPartition) tl
  in
  partitionHelper [] [] input;;

let buildCNF (input: string list) : (string * string) list list =
  let rec parseClause tokens =
    let rec parse acc tokens =
      match tokens with
      | [] -> List.rev acc
      | "AND" :: rest -> List.rev acc
      | "OR" :: rest -> parse acc rest
      | "NOT" :: v :: rest -> 
          if List.mem v validVarNames || v = "TRUE" || v = "FALSE" then
            parse ((v, "NOT") :: acc) rest
          else parse acc rest
      | v :: rest -> 
          if List.mem v validVarNames || v = "TRUE" || v = "FALSE" then
            parse ((v, "") :: acc) rest
          else parse acc rest
    in
    let parsed = parse [] tokens in
    if parsed = [] then None else Some parsed
  in
  
  let rec splitClauses tokens acc =
    match tokens with
    | [] -> List.rev acc
    | _ ->
        let rec findClause current rest =
          match rest with
          | [] -> (List.rev current, [])
          | "AND" :: remaining -> (List.rev current, remaining)
          | x :: xs -> findClause (x :: current) xs
        in
        
        let (clause, remaining) = findClause [] tokens in
        match parseClause clause with
        | Some parsedClause -> splitClauses remaining (parsedClause :: acc)
        | None -> splitClauses remaining acc
  in
  
  splitClauses input [];;

(* Get Variables Function *)
let getVariables (input: string list) : string list =
  let isValidVar token =
    List.mem token validVarNames || token = "TRUE" || token = "FALSE"
  in

  let rec extractVars inputList acc =
    match inputList with
    | [] -> acc
    | hd :: tl ->
        if isValidVar hd && not (List.mem hd acc) then
          extractVars tl (hd :: acc)
        else
          extractVars tl acc
  in

  extractVars input [];;

(* Generate Default Assignments Function *)
let rec generateDefaultAssignments (varList: string list) : (string * bool) list =
  match varList with
  | [] -> []
  | hd :: tl -> (hd, false) :: generateDefaultAssignments tl;;

let rec generateNextAssignments (assignList: (string * bool) list) : (string * bool) list * bool =
  (*dont forget to reverse the list! (i did and i only discovered it after 2 hours of debugging!!!!)*)
  let rec aux reversed =  
    match reversed with
    | [] -> ([], true) 
    | (var, false) :: rest -> 
        ((var, true) :: rest, false)
    | (var, true) :: rest -> 
        
        let nextRest, carry = aux rest in
        ((var, false) :: nextRest, carry)
  in
  let reversed_input = List.rev assignList in  
  let result, carry = aux reversed_input in
  (List.rev result, carry)  



(* Lookup Variable Function *)
let rec lookupVar (assignList: (string * bool) list) (str: string) : bool =
  match assignList with
  | [] -> raise (Invalid_argument "ERROR LOOKUPVAR NULL")  
  | (var, value) :: tl -> if var = str then value else lookupVar tl str;;

(* Evaluate CNF Function *)
let evaluateCNF (t: (string * string) list list) (assignList: (string * bool) list) : bool =
  let evaluateClause clause =
    List.exists (fun (var, neg) ->
      let varValue = lookupVar assignList var in
      if neg = "NOT" then not varValue else varValue
    ) clause
  in
  List.for_all evaluateClause t;;

(* Satisfy Function *)
let rec satisfy (input : string list) : (string * bool) list =
  let cnf = buildCNF input in
  let varList = getVariables input in
  
  if cnf = [] then 
    (* If no clauses, return default false assignments *)
    generateDefaultAssignments varList
  else
    let initialAssignments = generateDefaultAssignments varList in

    let rec tryAssignments assignments =
      if evaluateCNF cnf assignments then assignments
      else
        let nextAssignments, done_flag = generateNextAssignments assignments in
        (*exhausted list? gotta be true*)
        if done_flag then [("error", true)]
        else tryAssignments nextAssignments
    in
    tryAssignments initialAssignments;;
