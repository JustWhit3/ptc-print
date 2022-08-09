#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thr Jul 28 20:34:00 2022
Author: Gianluca Bianco
"""

#################################################
#     Modules
#################################################
import matplotlib.pyplot as plt
import doctest
import argparse as ap
from termcolor import colored as cl
import pandas as pd
import json
import os

#################################################
#     set_y_label
#################################################
def set_y_label( time_type ):
    """
    Function used to modify the input y label.

    Args:
        time_type (str): the input y label.

    Returns:
        str: the modified input y label.
    
    Testing:
        >>> set_y_label( "real_time" )
        'Real time'
        >>> set_y_label( "cpu_time" )
        'CPU time'
    """
    
    if time_type == "real_time":
        return "Real time"
    elif time_type == "cpu_time":
        return "CPU time"
    return ""

#################################################
#     set_x_ticks_label
#################################################
def set_x_ticks_label( x_tick ):
    """
    Function used to modify the x_tick label.

    Args:
        x_tick (str): the x_tick label.

    Returns:
        str: the modified x_tick label.
        
    Testing:
        >>> set_x_ticks_label( "ptc_print_str_mean" )
        'ptc::print'
        >>> set_x_ticks_label( "fmt_print_stdout_mean" )
        'fmt::print'
        >>> set_x_ticks_label( "std_cout_str_mean" )
        'std::cout'
        >>> set_x_ticks_label( "printf_stdout" )
        'printf'
    """
    
    if "fmt_" in x_tick or "ptc_" in x_tick or "std_" in x_tick:
        x_tick = x_tick.split( "_" )[0:2]
        x_tick = "::".join( x_tick )
    elif "printf_" in x_tick:
        x_tick = x_tick.split( "_" )[0:1]
        x_tick = " ".join( x_tick )
    
    return x_tick

#################################################
#     get_feature_name
#################################################
def get_feature_name( name ):
    """
    Function used to get feature name from a string.

    Args:
        name (str): the input string name.

    Returns:
        str: the feature name.
    
    Testing:
        >>> get_feature_name( "ptc_print_str" )
        'string initialization'
        >>> get_feature_name( "fmt_print_stdout" )
        'stdout stream'
    """
    
    if "str" in name:
        return "string initialization"
    elif "stdout" in name:
        return "stdout stream"
    elif "newline" in name:
        return "newline to stdout"
    elif "standard" in name:
        return "generic ostream"
    elif "file" in name:
        return "writing to file"

#################################################
#     Plotter
#################################################
def plotter( data, time_type ):
    """
    Function used to plot benchmarks.

    Args:
        data (json file): the input dataset.
        time_type (str): the data time-type.
    """
    
    # Loading data
    with open( data ) as f:
        data = json.load( f )

    # Variables
    fig, ax = plt.subplots()
    mean, std, names = [], [], []
    names = {}
    counter = 0
    colors = [ "red", "green", "blue", "orange", "pink", "cyan" ]
    
    # Doing plot
    for d in data[ "benchmarks" ]:
        if "mean" in d[ "name" ]:
            feature_name = get_feature_name( d[ "name" ] )
            names[ set_x_ticks_label( d[ "name" ] ) ] = counter
            counter += 1
            mean.append( d[ time_type ] )
        elif "stddev" in d[ "name" ]:
            std.append( d[ time_type ] )   
    plt.bar( names.keys(), mean, yerr = std, color = colors, capsize = 5 )

    # Adding mean value inside each chart
    for i in range( counter ):
        ax.text( -0.15 + i , 70, round( mean[ i ] ), color = "white", fontweight = "bold" )
        
    # Plot settings
    ax.set_xlabel( "Object / function" )
    ax.set_ylabel( "{} (ns)".format( set_y_label( time_type ) ) )
    if "Real" in ax.get_ylabel():
        ax.set_title( r'''$\bf{Real \ time \ benchmarks}$ (%(feature)s)'''% { "feature": feature_name } )
    elif "CPU" in ax.get_ylabel():
        ax.set_title( r'''$\bf{CPU \ time \ benchmarks}$ (%(feature)s)'''% { "feature": feature_name } )
    ax.yaxis.grid( True )
    ax.set_axisbelow( True )
        
    # Save plots
    if args.save == "no":
        plt.show()
    elif args.save == "yes":
        if args.macro == "yes":
            suffix = "_macro"
        elif args.macro == "no":
            suffix = ""
        else:
            raise RuntimeError( cl( "Inserted --macro option \"{}\" is not supported!".format( args.macro ), "red" ) )
        path = "../../img/benchmarks/{}".format( time_type )
        if not os.path.exists( path ):
            os.makedirs( path )
        plt.savefig( "../../img/benchmarks/{}/{}{}".format( time_type, feature_name.replace( " ", "_" ), suffix ) )
    else:
        raise RuntimeError( cl( "Inserted --save option \"{}\" is not supported!".format( args.save ), "red" ) )

#################################################
#     Main
#################################################
def main():
    plotter( args.data, "real_time" )
    plotter( args.data, "cpu_time" )

if __name__ == "__main__":

    # Parser settings
    parser = ap.ArgumentParser( description = "Parsing input file names." ) 
    parser.add_argument( "--tests", default = "on", help = "Enable/disable tests (yes / no)." )
    parser.add_argument( "--data", default = "data/benchmarking.json", help = "The input dataset." )
    parser.add_argument( "--save", default = "no", help = "Save the produced plots or not (yes / no)." )
    parser.add_argument( "--macro", default = "no", help = "Preprocessor macro usage (yes / no)." )
    args = parser.parse_args()
    
    # Main commands
    if args.tests == "on":
        doctest.testmod()
        main()
    elif args.tests == "off":
        main()
    else:
        raise RuntimeError( cl( "Inserted --tests option \"{}\" is not supported!".format( args.tests ), "red" ) )
