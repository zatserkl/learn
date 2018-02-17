# Andriy Zatserklyaniy <zatserkl@gmail.com> Apr 3, 2017

from datetime import datetime, timedelta
from collections import deque, defaultdict

class NoSignUTC(Exception):
    pass

class FormatError(Exception):
    pass

class LogAnalysis:
    """
    Method.
    For each failed ip we use a container buf_fail for 3 last failed login attempts.
    After third failed login we add an +5 minutes time moment to empty container time_unblock.
    Successful login clears the container buf_fail: removes the entry for this ip.
    """
    def __init__(self):
        self.debug = False
        # self.debug = True

        self.html_code_Unauthorized = 401       # HTML code for failed login attempt
        self.html_code_OK = 200                 # HTML code for successful login attempt

        # parameters
        self.time_range_fail = 20               # time in seconds range to count failed login attempts
        self.nfail = 3                          # the number of failed logins to be blocked
        self.nminutes = 5                       # block ip for nminutes

        # properties of the current event (line)
        self.ip = ''
        self.date_time_offset = ''              # string representation of time
        self.time = timedelta(0)                # datetime representation of time
        self.request = ''
        self.resourse = ''
        self.html_code = 0
        self.len_replay = 0
        self.time_local = timedelta(0)
        self.time_utc = timedelta(0)
        self.utc_offset = timedelta(0)          # UTC offset: info about time zone
        self.good_event = False

        self.extract_fields_init = True         # init constants of the method extract_fields

        # constant values to speedup initialization
        self.datetime_zero = datetime(1990, 1, 1, 0, 0, 0)      # level zero
        self.time_block = timedelta(0, self.nminutes*60)        # timedelta for block in seconds

        #
        # deque of constant length nfail for the last nfail elements
        #
        self.buf_fail = defaultdict(lambda: deque(self.nfail*[self.datetime_zero], maxlen=self.nfail))

        #
        # container for the value of time to unblock access for the failed ip
        #
        self.time_unblock = defaultdict(list)

        #
        # Analytics
        #

        # self.top_hours = []                     # pairs (time, nvisits)
        # self.bins = [0 for _ in range(2*3600)]  # bins (seconds) for 2 hours
        # self.time0 = self.datetime_zero         # time for the first bin
        # self.time0_offset = self.datetime_zero  # constant value of the UTC offset (for convenience)
        self.nhours = 10                          # top 10 hours
        self.top_hours = self.nhours*[('a', 0)]   # pairs (time, nvisits)
        self.busy_hours_init = True               # flag to init method busy_hours

        self.seconds = 10000000*[0]
        self.nseconds = 0

        self.time0_loc = self.datetime_zero

        self.hosts = defaultdict(int)           # host frequency

        self.resources = defaultdict(int)       # resources bandwidth

        # output files
        self.ofile_blocked_txt = open("blocked.txt", 'w')

    def process_file(self, fname):
        """
        Loops over the data file lines
        """

        line_start, nlines_max = 0, 0
        # line_start, nlines_max = 0, 20
        # line_start, nlines_max = 0, 1000
        # line_start, nlines_max = 0, 4000000
        # line_start, nlines_max = 1600000, 0
        # line_start, nlines_max = 0, 1         # the first line
        # line_start, nlines_max = 117, 10      # replay of zero bytes: hyphen
        # line_start, nlines_max = 0, 100        # the first line
        # line_start, nlines_max = 0, 10000        # the first line

        nlines = 0
        with open(fname, 'r') as file:
            for iline, self.line in enumerate(file):

                if iline % 1000000 == 0: print 'processing line', iline

                if iline < line_start:
                    continue

                nlines += 1
                if nlines_max > 0 and nlines > nlines_max:
                    break

                if nlines > 20:
                    self.debug = False          # forse debug off for large output

                try:
                    self.extract_fields()
                    self.parse_time()

                except FormatError as e:
                    print 'Format error in line', iline, e.args[0]
                    continue
                except ValueError:
                    print 'Format error (ValueError) in line', iline
                    continue
                except NoSignUTC as e:
                    print '***Warning parse_time: Caught NoSignUTC exception e.args[0]:', e.args[0]
                    continue

                if self.debug:
                    print iline, '\t', \
                        self.ip, self.date_time_offset, self.resource, self.html_code, self.len_replay, \
                        self.time_local, self.time_utc

                #
                # At this point we have all the information successfully extracted
                #

                self.runtime_block()

                #
                # run analytics
                #

                self.hosts[self.ip] += 1

                self.resources[self.resource] = self.len_replay

                self.busy_hours()       # collect busy hours info from each event

        #
        # Final processing after loop over events
        #

        #
        # Summarize busy hours
        #

        self.busy_hours_hist()          # process collected histogram

        #
        # The most frequent hosts
        #

        print '\nhosts:'
        nprint = 0
        with open("hosts.txt", "w") as ofile_hosts:
            for host in sorted(self.hosts, key=self.hosts.get, reverse=True):
                line = "%s, %d\n" % (host, self.hosts[host])
                print nprint, line,
                ofile_hosts.write(line)
                nprint += 1
                if nprint >= 10:
                    break

        #
        # The most bandwidth-hungry resources
        #

        print '\nresources:'
        nprint = 0
        with open("resources.txt", "w") as ofile_resources:
            for resource in sorted(self.resources, key=self.resources.get, reverse=True):
                line = "%s, %d\n" % (resource, self.resources[resource])
                print nprint, line,
                ofile_resources.write(line)
                nprint += 1
                if nprint >= 10:
                    break

    def extract_fields(self):
        """
        Extracts data fields from the original line:
        ip
        time string
        request string
        HTML code
        request length
        """

        # parse constants
        if self.extract_fields_init:
            self.ip_separator = ' - - '
            self.len_separator = len(self.ip_separator)
            self.len_date = len('01/Jul/1995:00:00:01 -0400')
            self.extract_fields_init = False

        self.good_event = False
        ip_end = self.line.find(self.ip_separator)    # one position after the ip
        if ip_end < 0:
            raise FormatError("Error in ip")
        self.ip = self.line[0: ip_end]

        self.date_time_offset = self.line[ip_end+self.len_separator+1: ip_end+self.len_separator+1+self.len_date]

        request_start = self.line.find('"')
        request_end = self.line.rfind('"')

        if request_start < 0:
            raise FormatError("Error in request")
        if request_end == request_start:
            raise FormatError("Error in request")

        self.request = self.line[request_start+1: request_end]

        resource_start = self.request.find(' ')              # one position before the request
        if resource_start < 0:
            raise FormatError("Error in resource")
        resource_end = self.request.rfind(' ')
        if resource_end < 0:
            raise FormatError("Error in resource")
        self.resource = self.request[resource_start+1: resource_end].strip(' \t\n\r')   # strip spaces

        code_bytes = self.line[request_end+1:].split()
        self.html_code = int(code_bytes[0])
        self.len_replay = 0
        if code_bytes[1] != '-': self.len_replay = int(code_bytes[1])

        self.good_event = True
        return

    def parse_time(self):
        """
        Processes time information:
        1) converts time string to datetime
        2) gets UTC time by adding the UTC offset
        """
        self.good_event = False

        tlist = self.date_time_offset.split()
        self.time_local = datetime.strptime(tlist[0], "%d/%b/%Y:%H:%M:%S")
        offset = tlist[1]

        self.time_utc = self.time_local
        self.utc_offset = timedelta(hours=int(offset[1:3]), minutes=int(offset[3:5]))

        if offset[0] == '+':
            self.time_utc = self.time_local + self.utc_offset
        elif offset[0] == '-':
            self.time_utc = self.time_local - self.utc_offset
        else:
            raise NoSignUTC('there is no sign in UTC offset')

        self.good_event = True

    def runtime_block(self):
        """
        Processes two HTML code: for failed login (401) and for successful login (200) attempts
        """
        if self.ip in self.time_unblock:
            #
            # this ip was blocked some time ago
            #
            if self.time_utc < self.time_unblock[self.ip][0]:
                #
                # attempt of access during the blocked time
                #
                self.ofile_blocked_txt.write(self.line) # make an entry into blocked.txt
                return                                  # done with this event
            else:
                #
                # block time was over, clear the time_unblock: remove the entry for the ip
                #
                self.time_unblock.pop(self.ip, None)
                #
                # analyse the request with the code below this if-section
                #

        # NB: the ip is not blocked at this point

        if self.html_code == self.html_code_Unauthorized:
            # add to the deque under index 0
            self.buf_fail[self.ip].appendleft(self.time_utc)
            # check the time difference with the first item
            delta = self.buf_fail[self.ip][0] - self.buf_fail[self.ip][-1]

            if delta.total_seconds() < self.time_range_fail:
                #
                # We detected 3 failed login attempts during 5 minutes interval
                #
                #-- print 'self.buf_fail[', self.ip, '][0]:', delta.total_seconds(), '   -->', self.date_time_offset

                # create a +5 minutes time_unblock for this ip
                time = self.time_utc + self.time_block
                self.time_unblock[self.ip].append(time)

        elif self.html_code == self.html_code_OK:
            # clear the history: remove the entry for the ip from the dictionary
            self.buf_fail.pop(self.ip, None)
        return

    def busy_hours(self):
        """
        Fills the histogram and sorted array for (time, nvisits) pairs
        """
        if self.busy_hours_init:
            # histograms
            #-- self.nhours = 10                                            # top 10 hours
            #-- self.top_hours = self.nhours*[0]                            # pairs (time, nvisits)
            #-- self.top_hours = self.nhours*[('a', 0)]                            # pairs (time, nvisits)
            #-- print 'self.top_hours:', self.top_hours

            # self.hour = 3600
            # self.nbins = 2*self.hour
            # #self.bins = [0 for _ in range(nbins)]                      # bins (seconds) for 2 hours
            # self.bins = deque(self.nbins*[0], maxlen=self.nbins)        # bins (seconds) for 2 hours
            # self.first = 0                                              # the first bin

            # use the first good event to init
            self.time0 = self.time_utc                  # time for the first bin
            self.time0_offset = self.utc_offset         # constant value of the UTC offset (for convenience)
            self.time0_loc = self.time_local
            self.busy_hours_init = False                # turn off initialization

        # # find the histogram bin for the current event
        # delta = self.time_utc - self.time0
        # bin = int(delta.total_seconds()) - self.first
        # if bin < self.hour:
        #     for ibin in range(bin):
        #         self.bins[(self.first + ibin) % self.nbins] += 1
        # else:
        #     #print '\nShift buffer\n'

        #     # the first bin went out of scope. Process it.
        #     nprocess = bin - self.hour
        #     for ibin in range(nprocess):
        #         # create pair
        #         time_dt = self.time0 + timedelta(0, ibin)       # add ibin seconds
        #         time_dt += self.time0_offset                    # convert to local time
        #         time_str = time_dt.strftime("%d/%b/%Y:%H:%M:%S")
        #         time_str += ' -0400'                            # TODO: use convert
        #         p = (time_str, self.bins[(self.first + ibin) % self.nbins])

        #         n = 0
        #         while p[1] < self.top_hours[n][1]:
        #             n += 1
        #             if n >= len(self.top_hours):
        #                 break

        #         self.top_hours.insert(n, p)
        #         self.top_hours.pop()            # remove last item

        #         self.first += 1
        #         self.time0 += timedelta(0, 1)   # add 1 second

        #     # print self.top_hours
        #     # for p in self.top_hours:
        #     #    print 'p:', p[0], p[1]

        #
        # Currently working algorithm
        #

        delta = self.time_utc - self.time0
        ikey = int(delta.total_seconds())
        if ikey >= 0 and ikey < 10000000:
            if ikey > self.nseconds:
                self.nseconds = ikey
            self.seconds[ikey] += 1
            # print 'ikey =', ikey
        else:
            print 'ikey =', ikey, 'out of range'

    def busy_hours_hist(self):
        """
        Processes busy hours histogram using moving average algorithm
        """
        # print 'self.nseconds =', self.nseconds
        # print 'self.time0_loc =', self.time0_loc.strftime("%d/%b/%Y:%H:%M:%S")
        # time_last = self.time0_loc + timedelta(0, self.nseconds)
        # print 'time_last =', time_last.strftime("%d/%b/%Y:%H:%M:%S")
        # print

        time_dt = self.time0_loc
        time_str = time_dt.strftime("%d/%b/%Y:%H:%M:%S")
        time_str += ' +0400'
        visits = sum(self.seconds[:3600])
        p = (time_str, visits)
        self.top_hours[0] = p

        isec = 1
        while isec + 3600 < self.nseconds:
            visits += self.seconds[isec+3600] - self.seconds[isec-1]
            time_dt = self.time0_loc + timedelta(0, isec)
            time_str = time_dt.strftime("%d/%b/%Y:%H:%M:%S")
            time_str += ' +0400'
            p = (time_str, visits)

            n = 0
            while p[1] < self.top_hours[n][1]:
                n += 1
                if n >= len(self.top_hours):
                    break

            self.top_hours.insert(n, p)
            self.top_hours.pop()

            isec += 1                   # increament the loop variable

        with open("hours.txt", "w") as ofile_hours:
            for p in self.top_hours:
                line = "%s, %d\n" % (p[0], p[1])
                print line,
                ofile_hours.write(line)

# 14   burger.letters.com - - [01/Jul/1995:00:00:12 -0400] "GET /images/NASA-logosmall.gif HTTP/1.0" 304 0
# 15   burger.letters.com - - [01/Jul/1995:00:00:12 -0400] "GET /shuttle/countdown/video/livevideo.gif HTTP/1.0" 200 0

# 215.298.34.27 - - [01/Jul/1995:03:27:20 -0400] "POST /login HTTP/1.0" 401 1420
# 215.298.34.27 - - [01/Jul/1995:03:27:21 -0400] "POST /login HTTP/1.0" 401 1420
# 215.298.34.27 - - [01/Jul/1995:03:27:22 -0400] "POST /login HTTP/1.0" 401 1420
# 215.298.34.27 - - [01/Jul/1995:03:27:25 -0400] "POST /login HTTP/1.0" 401 1420
# 215.298.34.27 - - [01/Jul/1995:03:27:26 -0400] "GET / HTTP/1.0" 200 7074
# 215.298.34.27 - - [01/Jul/1995:03:27:27 -0400] "GET /images/launch-logo.gif HTTP/1.0" 200 1713


logAnalysis = LogAnalysis()
logAnalysis.process_file('fansite-analytics-challenge-az/log_input/log.txt')

print
print 'len(logAnalysis.buf_fail) =', len(logAnalysis.buf_fail)
