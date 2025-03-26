<!-- *********************************************************************** -->
<!--                                                                         -->
<!--                                                      :::      ::::::::  -->
<!-- parsing.md                                         :+:      :+:    :+:  -->
<!--                                                  +:+ +:+         +:+    -->
<!-- By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+       -->
<!--                                              +#+#+#+#+#+   +#+          -->
<!-- Created: 2025/03/20 12:59:57 by lud-adam          #+#    #+#            -->
<!-- Updated: 2025/03/20 13:28:40 by lud-adam         ###   ########.fr      -->
<!--                                                                         -->
<!-- *********************************************************************** -->

# Parsing #

## Single quote

### Si '$PATH'
    Si '$PATH' Obtient $PATH

### Si ''$PATH''
     /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/lud-adam/.local/bin:/home/lud-adam/bin

### Si '''$PATH'''
    $PATH

### Si ''''$PATH''''
    /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/lud-adam/.local/bin:/home/lud-adam/bin

### Si '"'$PATH'"'
    "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/lud-adam/.local/bin:/home/lud-adam/bin"

### Si 'n_importe_quelle_mot'
    n_importe_quelle_mot

### Si ''n_importe_quelle_mot''
    n_importe_quelle_mot

### Si '''n_importe_quelle_mot'''
    n_importe_quelle_mot
etc..

### Si '"blabla"'
    "blabla"

### Si 'blabla
    quote>

### Si blabla'
    quote>

## Double quote

### Si "$PATH"
    /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/lud-adam/.local/bin:/home/lud-adam/bin

### Si ""$PATH"" ou si """$PATH""" etc..
    /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/lud-adam/.local/bin:/home/lud-adam/bin

### Si "'$PATH'"
    '/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/lud-adam/.local/bin:/home/lud-adam/bin'

### Si ""'$PATH'""
    $PATH

### Si """'$PATH'"""
    '/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/lud-adam/.local/bin:/home/lud-adam/bin'
    
### Si """"'$PATH'""""
    $PATH

etc

### Si "blabla
    dquote>

### Si blabla"
    dquote>

