setGeneric("fromYAML",
           function(stream, simplify = TRUE, simplifyWithNames = TRUE, null = NULL, encoding = NA, ...) 
               standardGeneric("fromYAML"))


setMethod("fromYAML", "AsIs",
           function(stream, simplify = TRUE, simplifyWithNames = TRUE, null = NULL, encoding = NA, ...) {

             txt = paste(stream, collapse = "\n")
             
           })

setMethod("fromYAML", "character",
           function(stream, simplify = TRUE, simplifyWithNames = TRUE, null = NULL, encoding = NA, ...) {

             if(file.exists(stream)) {
               .Call("R_readYAML", stream, TRUE, simplify, null, simplifyWithNames, encoding)
             } else {
                txt = readLines(stream)
                fromYAML(I(paste(txt, collapse = "\n")), simplify, simplifyWithNames, null, encoding, ...)
             }
             
           })

