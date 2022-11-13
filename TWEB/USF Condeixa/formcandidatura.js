window.onload = function () {
    init(); 
};

var form = document.querySelector('form');
var btnSubmissao = document.querySelector('#btnSubmeter');

form.addEventListener('submit', function (event) {
    event.preventDefault();
});


btnSubmissao.addEventListener('click', validaFormulario);
btnReset.addEventListener('click',init);

function validaFormulario(){
    if (form.checkValidity()){
        //Especificar as validações aqui
        
        if(!validaNome(pNome)){
            pNome.setCustomValidity('Nome inválido! Especifique o primeiro nome!');
            return;
        }
        if(!validaNome(uNome)){
            uNome.setCustomValidity('Nome inválido! Especifique o último nome!');
            return;
        }
        
        if(!validaCC(cartaoc)){
            cartaoc.setCustomValidity('Número inválido! Especifique um número com 8 dígitos!');
            return;
        }
        
        if( morada.value.length <15){
            morada.setCustomValidity('Introduza a morada completa!');
            return;
        }
        
        if( areatexto1.value.length <30){
            areatexto1.setCustomValidity('O motivo deve ser mais detalhado!');
            return;
        }
    
         //Submeter aqui
        document.getElementById("myform").submit();
		alert("Formulário inserido com sucesso!");
    }
    else{
       form.querySelectorAll(':invalid')[0].focus(); 
	   
    }  

}

//Padrao validar
function validaNome(fld) {
    var letters = /^[A-zÀ-ú]+$/; //o comeco da string é uma letra e no fim um dolar
    if (fld.value.trim().match(letters)) 
		return true;
    return false;
}

function validaCC(fld){
    var numbers=/^[0-9]+$/;
    if (fld.value.trim().match(numbers) && cartaoc.value.length ==8)
        return true;
    return false;
}

function init() {
     resetPainel();
}

function resetPainel(){
    pNome.setCustomValidity('');
    uNome.setCustomValidity('');
    cartaoc.setCustomValidity('');
    morada.setCustomValidity('');
    areatexto1.setCustomValidity('');
}



pNome.oninput=resetPainel;
uNome.oninput=resetPainel;
cartaoc.oninput=resetPainel;
morada.oninput=resetPainel;
areatexto1.oninput=resetPainel;