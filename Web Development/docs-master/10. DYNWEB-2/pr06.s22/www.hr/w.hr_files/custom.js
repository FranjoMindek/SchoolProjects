$(document).ready(function () {

    $('#step-one-next-button').click(function(ev) {
        ev.preventDefault();
        var checkUrl = checkLenUrl();
        if (checkUrl){
            $.ajax({
               type: 'POST',
               url: "/ajax/pageinfo",
               data: { url:$("#page-url").val() },
               success:    function(data) {
                            if (data.error != null){
                                $("#step-one-next-button").removeClass("btn-info").removeClass("btn-success").addClass("btn-danger");
                                $("#page-url").parent().addClass("has-error");
                                $("#page-url").siblings(".help-block").text(data.error);
                                $("div#step-one-next-button").attr("disabled", true);
                                $("#name-hr").val("");
                                $("#name-en").val("");
                                $("#keywords").val("");
                                $("#description-hr").val("");
                                $("#description-en").val("");
                                $("#location-street").val("");
                                $("#location-city").val("");
                                $("#location-county").val("");
                                $("#location-country").val("");
                            }
                            else if (data.error == null){
                                $("#step-one-next-button").removeClass("btn-info").removeClass("btn-danger").addClass("btn-success");
                                $("div#step-one-next-button").attr("disabled", false);
                                $("#page-url").parent().removeClass("has-error");
                                $("#page-url").siblings(".help-block").text("URL je ispravan");
                                $("#name-hr").val(data.pageMetaData.title);
                                $("#name-en").val(data.pageMetaData.title_en);
                                $("#keywords").val(data.pageMetaData.keywords);
                                $("#description-hr").val(data.pageMetaData.description);
                                $("#description-en").val(data.pageMetaData.description_en);
                                $("#location-street").val(data.pageMetaData.street);
                                $("#location-city").val(data.pageMetaData.city);
                                $("#location-county").val(data.pageMetaData.county);
                                $("#location-country").val(data.pageMetaData.country);
                                if (data.modification != false)
                                {
                                    $("#modification").val(data.modification);
                                }
                                if (data.pageMetaData.email != null)
                                {
                                    $("#page-url").siblings(".help-block").text("Stranica već postoji u katalogu!");
                                }
                                $("div#add-page-form-step-one").removeClass("show").addClass("hidden");
                                $("div#add-page-form-step-two").removeClass("hidden").addClass("show");
                            }
                        },
               dataType: "json",
               async:true
            });
        }
        else
        {
            $("#step-one-next-button").removeClass("btn-info").removeClass("btn-success").addClass("btn-danger");
            $("div#step-one-next-button").attr("disabled", true);
            $("#page-url").parent().addClass("has-error");
            $("#page-url").siblings(".help-block").text("Internet adresa sjedišta je prekratka");
        }
    });
    
    $("#page-url").click(function(){
         $("#step-one-next-button").removeClass("btn-danger").addClass("btn-info");
         $("div#step-one-next-button").attr("disabled", false);
         $("#page-url").parent().removeClass("has-error");
         $("#page-url").siblings(".help-block").text("URL adresa vaše stranice (npr. http://www.domena.hr).");
    });

    
    $("div#step-two-previous-button").click(function(){
        $("div#add-page-form-step-one").removeClass("hidden").addClass("show");
        $("div#add-page-form-step-two").removeClass("show").addClass("hidden");
    });
    $("div#step-two-next-button").click(function(){
        if (next())
        {
            $.ajax({
                   type: 'POST',
                   url: "/ajax/suggestcategory",
                   data: { keywords: $("#keywords").val()},
                   success:    function(data) {
                                if (data != ""){
                                    $("#predlozeneKategorije").empty();
                                    for (i in data)
                                    {
                                        $("#predlozeneKategorije").append("<p><label><input type='checkbox' class='category-checkbox' name='category[]' value='"+data[i].id+"'> " + data[i].name + "</label></p>");
                                    }
                                    window.scrollTo(0,0);
                                    $("div#add-page-form-step-two").removeClass("show").addClass("hidden");
                                    $("div#add-page-form-step-three").removeClass("hidden").addClass("show");
                                }
                                else
                                {
                                    $("#predlozeneKategorije").empty();
                                    $("#select-category-help-text").empty();
                                    $("#select-category-help-text").append("Nismo pronašli odgovarajuću kategoriju za vašu stranicu. Administrator će kategoriju odabrati prilikom pregleda i odobravanja prijave.");
                                    window.scrollTo(0,0);
                                    $("div#add-page-form-step-two").removeClass("show").addClass("hidden");
                                    $("div#add-page-form-step-three").removeClass("hidden").addClass("show");
                                }
                            },
                   dataType: "json",
                   async:true
                });
        }
        else
        {
            $("#step-two-next-button").removeClass("btn-info").addClass("btn-danger");
        }
    });
    $("div#step-three-previous-button").click(function(){
        $("div#add-page-form-step-two").removeClass("hidden").addClass("show");
        $("div#add-page-form-step-three").removeClass("show").addClass("hidden");
    });

    $("div#step-three-next-button").click(function(){
        $("div#add-page-form-step-four").removeClass("hidden").addClass("show");
        $("div#add-page-form-step-three").removeClass("show").addClass("hidden");
    });

    $("div#step-four-previous-button").click(function(){
        $("div#add-page-form-step-three").removeClass("hidden").addClass("show");
        $("div#add-page-form-step-four").removeClass("show").addClass("hidden");
    });
    
    $("div#step-four-next-button").click(function(){
        $("div#add-page-form-step-five").removeClass("hidden").addClass("show");
        $("div#add-page-form-step-four").removeClass("show").addClass("hidden");
    });
    $("div#step-five-previous-button").click(function(){
        $("div#add-page-form-step-four").removeClass("hidden").addClass("show");
        $("div#add-page-form-step-five").removeClass("show").addClass("hidden");
    });
});
