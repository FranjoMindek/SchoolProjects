function setHighContrast() {
	window.localStorage.setItem("highContrast", "true");
	jQuery('.page').addClass('page--high-contrast');
	jQuery('.search-menu-container').addClass('high-contrast-textblock');
	jQuery('.navbar-collapse').addClass('high-contrast-textblock');
	jQuery('.container-fluid').addClass('high-contrast-textblock');
	jQuery('.cbp-l-caption-title').addClass('cbp-l-caption-title--high-contrast');
	jQuery('.footer').addClass('high-contrast-textblock');
	jQuery('.accessibility-toolbar').addClass('accessibility-toolbar--high-contrast');
	jQuery('.content-banner').addClass('content-banner--high-contrast');
	jQuery('.subcategory-link').addClass('high-contrast-textblock');
	jQuery('.content-container').addClass('content-container--high-contrast');
	jQuery('.category-banner-container').addClass('category-banner-container--high-contrast');
	jQuery('.category-container').addClass('category-container--high-contrast');
	jQuery('.cbp-caption-defaultWrap').addClass('category-caption--high-contrast');
	jQuery('.site-name').addClass('text--high-contrast');
	jQuery('.site-url').addClass('text--high-contrast');
	jQuery('.site-description').addClass('text--high-contrast');
	jQuery('.btn-info').addClass('btn-info--high-contrast');
	jQuery('.btn-danger').addClass('btn-danger--high-contrast');
	jQuery('.infographic-wrapper').addClass('infographic-wrapper--high-contrast');
}

function setDefaultContrast() {
	window.localStorage.setItem("highContrast", "false");
	jQuery('.page').removeClass('page--high-contrast');
	jQuery('div').removeClass('high-contrast-textblock');
	jQuery('a').removeClass('high-contrast-textblock');
	jQuery('.accessibility-toolbar').removeClass('accessibility-toolbar--high-contrast');
	jQuery('.cbp-l-caption-title').removeClass('cbp-l-caption-title--high-contrast');
	jQuery('.content-banner').removeClass('content-banner--high-contrast');
	jQuery('.content-container').removeClass('content-container--high-contrast');
	jQuery('.category-banner-container').removeClass('category-banner-container--high-contrast');
	jQuery('.category-container').removeClass('category-container--high-contrast');
	jQuery('.cbp-caption-defaultWrap').removeClass('category-caption--high-contrast');
	jQuery('.site-name').removeClass('text--high-contrast');
	jQuery('.site-url').removeClass('text--high-contrast');
	jQuery('.site-description').removeClass('text--high-contrast');
	jQuery('.btn-info').removeClass('btn-info--high-contrast');
	jQuery('.btn-danger').removeClass('btn-danger--high-contrast');
	jQuery('.infographic-wrapper').removeClass('infographic-wrapper--high-contrast');
}

function setBiggerFontSize() {
	var fontIncrement =  window.localStorage.getItem("fontIncrement");
	var fontIncrementInt = parseInt(fontIncrement);
	var elements = ['body', '.subcategory-link', '.footer .menu', '.cbp-l-caption-title', '.category-caption-text', '.footer .copyright'];
	if (fontIncrementInt < 12 || fontIncrement === null) {
		for (i = 0, len=elements.length; i < len; i++) {
			var k = parseInt(jQuery(elements[i]).css('font-size'));
			var increasedSize = k + 2;
			jQuery(elements[i]).css('font-size', increasedSize);
		}
		if (fontIncrement === null) {
			jQuery('.page').addClass('page--increased-font-size');
			window.localStorage.setItem("fontIncrement", "2");
		} else {
			fontIncrementInt += 2;
			window.localStorage.setItem("fontIncrement", fontIncrementInt.toString());
		}
	}
}

function setSmallerFontSize() {
	var fontIncrement =  window.localStorage.getItem("fontIncrement");
	var fontIncrementInt = parseInt(fontIncrement);

	var elements = ['body', '.subcategory-link', '.footer .menu', '.cbp-l-caption-title', '.category-caption-text', '.footer .copyright'];
	if (fontIncrementInt < 12  || fontIncrementInt > -4 || fontIncrement === null) {
		for (i = 0, len=elements.length; i < len; i++) {
			var k = parseInt(jQuery(elements[i]).css('font-size'));
			var decreasedSize = k - 2;
			jQuery(elements[i]).css('font-size', decreasedSize);
		}
		if (fontIncrement === null) {
			jQuery('.page').addClass('page--increased-font-size');
			window.localStorage.setItem("fontIncrement", "-2");
		} else {
			fontIncrementInt -= 2;
			window.localStorage.setItem("fontIncrement", fontIncrementInt.toString());
		}
	}
}

function setDefaultFontSize() {
	var fontIncrement =  window.localStorage.getItem("fontIncrement");
	var fontIncrementInt = parseInt(fontIncrement);

	var elements = ['body', '.subcategory-link', '.footer .menu', '.cbp-l-caption-title', '.category-caption-text', '.footer .copyright'];
	for (i = 0, len=elements.length; i < len; i++) {
		var k = parseInt(jQuery(elements[i]).css('font-size'));
		var originalSize = k - fontIncrementInt;
		jQuery(elements[i]).css('font-size', originalSize);
	}
	window.localStorage.setItem("fontIncrement", "0");
}

function setOmoTypeFont() {
	var elements = ['body', '.cbp-l-caption-title', '.category-caption-text', '.infographic-serif-font'];
	jQuery('.page').addClass('page--omotype-font');
	window.localStorage.setItem("OmoType", "true");
	for (i = 0, len=elements.length; i < len; i++) {
		jQuery(elements[i]).css({'font-family': 'OmoType-BlackStdFour'});
	}
}

function setDefaultFont() {
	var elements = ['body', '.cbp-l-caption-title', '.category-caption-text', '.infographic-serif-font'];
	window.localStorage.setItem("OmoType", "false");
	jQuery('.page').removeClass('page--omotype-font');
	for (i = 0, len=elements.length; i < len; i++) {
		if (i===3) {
			jQuery(elements[i]).css({'font-family': 'Times New Roman, serif'});
		} else {
			jQuery(elements[i]).css({'font-family': 'Fira Sans, sans-serif'});
		}
	}
}

jQuery(document).ready(function() {
	/*-----------------------------------------------------------------------------------*/
	/*	CUBE PORTFOLIO
	 /*-----------------------------------------------------------------------------------*/
	jQuery('#js-grid-inline').cubeportfolio({
		filters: '#js-inline-filter',
		layoutMode: 'mosaic',
		mediaQueries: [{
			width: 1100,
			cols: 4
		}, {
			width: 800,
			cols: 3
		}, {
			width: 670,
			cols: 2
		}, {
			width: 320,
			cols: 1
		}],
		defaultFilter: '*',
		animationType: 'quicksand',
		gapHorizontal: 1,
		gapVertical: 1,
		gridAdjustment: 'responsive',
		caption: 'opacity',
		displayType: 'fadeIn',
		displayTypeSpeed: 100,

		// singlePageInline
		singlePageInlineDelegate: '.cbp-singlePageInline',
		singlePageInlinePosition: 'top',
		singlePageInlineInFocus: true
	});

	var topNavbar = jQuery('#top-navbar');
	var topNavbarDivider = topNavbar.find('.divider');
	var topNavbarToggleBtn = jQuery('#top-navbar-toggle-btn');

	topNavbarToggleBtn.on('click', function(e) {

		e.preventDefault();
		e.stopPropagation();

		if (!topNavbar.hasClass('expanded')) {
			topNavbar.addClass('expanded');
			topNavbar.slideDown();
		} else {
			topNavbar.slideUp(function() {
				topNavbar.removeClass('expanded');
			});
		}

	});

	// Active link
	var path_arr = location.pathname.split('/');
	var current = path_arr[path_arr.length - 1];
	jQuery('li a').each(function(){
		var href_arr = jQuery(this).attr('href').split("/");
		if (href_arr.length - 1 >= 0){
			var last_href = href_arr[href_arr.length - 1];
			if((current === "" && last_href.startsWith("www")) || ((current !== "") && last_href === current) || ((current !== "") && location.pathname.split('/').includes(last_href))){
				jQuery(this).parent().addClass('active');
			}
			if ((location.pathname.split('/').includes("onama") || location.pathname.split('/').includes("about"))  && last_href !== current) {
				jQuery(this).parent().removeClass('active');
			}
			if ((location.pathname.split('/').includes("katalog") || location.pathname.split('/').includes("description")) && last_href !== current && this.innerText === "PREGLED KATALOGA") {
				jQuery(this).parent().removeClass('active');
			}
		}
	})
});

function changeFontSize(target) {
    var contentWrapper = document.getElementsByClassName("content-wrapper")[0];
    var subcategoryLinks = document.getElementsByClassName("subcategory-link");

    var computedStyle = window.getComputedStyle
        ? getComputedStyle(contentWrapper) // Standards
        : contentWrapper.currentStyle;     // Old IE

    var computedStyleLink = window.getComputedStyle
        ? getComputedStyle(subcategoryLinks[0])
        : subcategoryLinks[0].currentStyle;

    var fontSize;
    var fontSizeLink;
    const maxFontSize = 46;
    const minFontSize = 8;
    if (computedStyle && computedStyleLink) { // This will be true on nearly all browsers
        fontSize = parseFloat(computedStyle && computedStyle.fontSize);
        fontSizeLink = parseFloat(computedStyleLink && computedStyleLink.fontSize);

        if (target == document.getElementById("button1")) {
            if (fontSize < maxFontSize) {
                fontSize += 2;
                fontSizeLink += 2;
            }
        } else if (target == document.getElementById("button2")) {
            if (fontSize > minFontSize) {
                fontSize -= 2;
                fontSizeLink -= 2;
            }
        }
        contentWrapper.style.fontSize = fontSize + "px";

        for (i = 0, len=subcategoryLinks.length; i < len; i++) {
            var subcategoryLink = subcategoryLinks[i];
            subcategoryLink.style.fontSize = fontSizeLink + "px";
        }
    }
}

jQuery(document).ready(function() {
	jQuery('#btn-toggle-contrast').click(function() {
		if (jQuery('.page').hasClass('page--high-contrast')) {
			setDefaultContrast();
		} else {
			setHighContrast();
		}
	});

	jQuery('#btn-fsize-bigger').click(function() {
		var fontIncrement =  window.localStorage.getItem("fontIncrement");
		var fontIncrementInt = parseInt(fontIncrement);
		var elements = ['body', '.subcategory-link', '.footer .menu', '.cbp-l-caption-title', '.category-caption-text', '.footer .copyright'];
		if (fontIncrementInt < 12 || fontIncrement === null) {
			for (i = 0, len=elements.length; i < len; i++) {
				var k = parseInt(jQuery(elements[i]).css('font-size'));
				var increasedSize = k + 2;
				jQuery(elements[i]).css('font-size', increasedSize);
			}
			if (fontIncrement === null) {
				jQuery('.page').addClass('page--increased-font-size');
				window.localStorage.setItem("fontIncrement", "2");
			} else {
				fontIncrementInt += 2;
				window.localStorage.setItem("fontIncrement", fontIncrementInt.toString());
			}
		}
		console.log(window.localStorage.getItem("fontIncrement"));
	});

	jQuery('#btn-fsize-smaller').click(function() {
		var fontIncrement =  window.localStorage.getItem("fontIncrement");
		var fontIncrementInt = parseInt(fontIncrement);

		var elements = ['body', '.subcategory-link', '.footer .menu', '.cbp-l-caption-title', '.category-caption-text', '.footer .copyright'];
		if (fontIncrementInt < 12  || fontIncrementInt > -4 || fontIncrement === null) {
			for (i = 0, len=elements.length; i < len; i++) {
				var k = parseInt(jQuery(elements[i]).css('font-size'));
				var decreasedSize = k - 2;
				jQuery(elements[i]).css('font-size', decreasedSize);
			}
			if (fontIncrement === null) {
				jQuery('.page').addClass('page--increased-font-size');
				window.localStorage.setItem("fontIncrement", "-2");
			} else {
				fontIncrementInt -= 2;
				window.localStorage.setItem("fontIncrement", fontIncrementInt.toString());
			}
		}
		console.log(window.localStorage.getItem("fontIncrement"));
	});

	jQuery('#btn-toggle-font').click(function() {
		if (jQuery('.page').hasClass('page--omotype-font')) {
			setDefaultFont();
		} else {
			setOmoTypeFont();
		}
	});

	jQuery('#btn-return-default').click(function () {
		setDefaultContrast();
		setDefaultFontSize();
		setDefaultFont();

		localStorage.removeItem("highContrast");
		localStorage.removeItem("fontIncrement");
		localStorage.removeItem("OmoType");
	})

});

jQuery(document).ready(function() {
	if (window.localStorage.getItem("fontIncrement")){
		var elements = ['body', '.subcategory-link', '.footer .menu', '.cbp-l-caption-title', '.category-caption-text', '.footer .copyright'];
		for (i = 0, len=elements.length; i < len; i++) {
			var size = parseInt(window.localStorage.getItem("fontIncrement"));
			var k = parseInt(jQuery(elements[i]).css('font-size'));
			var increasedSize = k + size;
			jQuery(elements[i]).css('font-size', increasedSize);
		}
	}

	if (window.localStorage.getItem("highContrast") === "true") {
		setHighContrast();
	}

	if (window.localStorage.getItem("OmoType") === "true") {
		setOmoTypeFont();
	}
 });
