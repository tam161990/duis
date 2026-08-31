#!/bin/bash
echo "==========================================="
echo "POSTFIX MAIL QUEUE AND LOGS CHECK"
echo "==========================================="
echo ""

echo "1. Mail Queue Status:"
echo "-------------------------------------------"
mailq
echo ""

echo "2. Recent Postfix Logs (last 50 lines):"
echo "-------------------------------------------"
tail -n 50 /var/log/maillog | grep -E "(postfix|C4E1E2005253)"
echo ""

echo "3. Search for our test email (C4E1E2005253):"
echo "-------------------------------------------"
grep "C4E1E2005253" /var/log/maillog
echo ""

echo "4. Check Postfix main configuration:"
echo "-------------------------------------------"
postconf | grep -E "(relayhost|mydestination|inet_interfaces)"
echo ""

echo "==========================================="
