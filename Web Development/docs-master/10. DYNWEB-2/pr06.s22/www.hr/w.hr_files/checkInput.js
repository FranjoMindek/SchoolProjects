$(document).ready(function () {
    var helpBlockName = $("#name-hr").siblings(".form-group").find(".help-block").text();
    var helpBlockNameEn = $("#name-en").siblings(".form-group").find(".help-block").text();
    var helpBlockDescription = $("#description-hr").siblings(".form-group").find(".help-block").text();
    var helpBlockKeywords = $("#keywords").siblings(".form-group").find(".help-block").text();
    var helpBlockRegistrant = $("#registrant").siblings(".form-group").find(".help-block").text();
    var timeoutReference;
    emailRegex = /^([\w-\.]+)@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.)|(([\w-]+\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\]?)$/;
    
    $("#name-hr").blur(function(){checkLen("#name-hr", "Naziv stranice ne smije biti prazan! ", helpBlockName)}); 
    $("#name-en").blur(function(){checkLen("#name-en", "Naziv stranice ne smije biti prazan! ", helpBlockNameEn)}); 
    $("#description-hr").blur(function(){checkLen("#description-hr", "Opis stranice ne smije biti prazan! ", helpBlockDescription)});
    $("#keywords").blur(function(){checkLen("#keywords", "Potrebno je unijeti barem jednu ključnu riječ! ", helpBlockKeywords)});
    $("#step-four-next-button").click(showSubmit);
    $('#registrant').keypress(function() {
        var _this = $(this);
        if (timeoutReference) clearTimeout(timeoutReference);
        timeoutReference = setTimeout(function() {
            checkLen("#registrant", "Molimo, unesite svoje ime! ", helpBlockRegistrant);
            showSubmit();
        }, 100);
    });
    $('#email').keypress(function() {
        var _this = $(this);
        if (timeoutReference) clearTimeout(timeoutReference);
        timeoutReference = setTimeout(function() {
            checkMail();
            showSubmit();
        }, 100);
    });
});

function checkLenUrl(){
    if ($("#page-url").val().length < 3){
        return false;
    }
    else if ($("#page-url").val().length >= 3){
        return true;
    }
}

function checkLen(attr,error, helpBlock, check){
    if ($(attr).val().length == 0){
        $(attr).parent().addClass("has-error");
        $(attr).siblings(".form-group").find(".help-block").text(error + helpBlock);
        $(attr).focus();
        $("#step-two-next-button").removeClass("btn-info").addClass("btn-danger");
    }

    else if ($(attr).val() != 0){
            $(attr).parent().removeClass("has-error");
            $(attr).siblings(".form-group").find(".help-block").text(helpBlock);
            $("#step-two-next-button").removeClass("btn-danger").addClass("btn-info");
    }

    showSubmit();
}

function checkMail(){
    if ($("#email").val().length == 0){
        $("#email").parent().addClass("has-error");
        $("#email").siblings(".form-group").find(".help-block").text("Molimo, unesite Vaš e-mail!");
        $("#email").focus();
         $("#step-two-next-button").removeClass("btn-info").addClass("btn-danger");
    }

    else if ($("#email").val() != 0){
        if(!emailRegex.test($("#email").val())){
            $("#email").parent().addClass("has-error");
            $("#email").siblings(".form-group").find(".help-block").text("E-mail koji ste unijeli nije ispravan! Molimo, unesite Vaš e-mail!");
            $("#email").focus();
             $("#step-two-next-button").removeClass("btn-info").addClass("btn-danger");
        }
        else{
            $("#email").parent().removeClass("has-error");
            $("#email").siblings(".form-group").find(".help-block").text("");
            $("#step-two-next-button").removeClass("btn-danger").addClass("btn-info");
        }
    }
    
   showSubmit();
}

/*
function next(){
    if (($("#name-hr").val() == 0) || ($("#description-hr").val() == 0) || ($("#keywords").val() == 0) ||
        ($("#registrant").val() == 0) || ($("#email").val() == 0) || ((!emailRegex.test($("#email").val())))){

        return false;
    }
    else{
        return true;
    }
}
*/

function next(){
    if (($("#name-hr").val() == 0) || ($("#name-en").val() == 0) || ($("#description-hr").val() == 0) || ($("#keywords").val() == 0))
    {
        var helpBlockName = $("#name-hr").siblings(".form-group").find(".help-block").text();
        var helpBlockNameEn = $("#name-en").siblings(".form-group").find(".help-block").text();
        var helpBlockDescription = $("#description-hr").siblings(".form-group").find(".help-block").text();
        var helpBlockKeywords = $("#keywords").siblings(".form-group").find(".help-block").text();
        checkLen("#name-hr", "Naziv stranice ne smije biti prazan! ", helpBlockName); 
        checkLen("#name-en", "Naziv stranice ne smije biti prazan! ", helpBlockNameEn); 
        checkLen("#description-hr", "Opis stranice ne smije biti prazan! ", helpBlockDescription);
        checkLen("#keywords", "Potrebno je unijeti barem jednu ključnu riječ! ", helpBlockKeywords);
        return false;
    }
    else
    {
        return true;
    }
}

function showSubmit(){
    if (($("#name-hr").val() == 0) || ($("#name-en").val() == 0) || ($("#description-hr").val() == 0) || ($("#keywords").val() == 0) ||
        ($("#registrant").val() == 0) || ($("#email").val() == 0) || ((!emailRegex.test($("#email").val())))){
        
        $("#step-five-submit-button").removeClass("btn-success").addClass("btn-danger").attr("disabled", true);
    }
    else{
        $("#step-five-submit-button").removeClass("btn-danger").addClass("btn-success").attr("disabled", false);
    }
 
}

