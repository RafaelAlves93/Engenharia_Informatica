window.onload = function () {
    init(); 
};

var form = document.querySelector('form');
var btnSubmissao = document.querySelector('#btnSubmit');

form.addEventListener('submit', function (event) {
    event.preventDefault();
});


btnSubmissao.addEventListener('click', validaFormulario);


function validaFormulario(){
    if (form.checkValidity()){
        //Especificar as validações aqui
        
        if(!validaNome(primeironome)){
            primeironome.setCustomValidity('Nome inválido! Especifique o primeiro nome!');
            return;
        }
        if(!validaNome(ultimonome)){
            ultimonome.setCustomValidity('Nome inválido! Especifique o último nome!');
            return;
        }
        
        if( assunto.value.length <20){
            assunto.setCustomValidity('Pf deixe uma mensagem mais detalhada!');
            return;
        }
         //Submeter aqui
        document.getElementById("mensagem").submit();
		alert("Formulário submetido com sucesso!");
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

function init() {
     resetPainel();
}

function resetPainel(){
    
primeironome.setCustomValidity('');
ultimonome.setCustomValidity('');
assunto.setCustomValidity('');
    
}

primeironome.oninput=resetPainel;
ultimonome.oninput=resetPainel;
assunto.oninput=resetPainel;


